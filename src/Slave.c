#include <P18F4520.h>
#include "Utils.h"
#include "spiSlave.h"
#include "PIC18Flash.h"
#include "SegmentHandler.h"
#define JumpPin PORTCbits.RC0 
#define Write 0x11
#define Read 0x22
#define CONFIG 0x33
#define DevID 0x44
#define Done 0xFF

#pragma config OSC = INTIO67 , PWRT = ON , WDT = OFF , DEBUG = ON , LVP =OFF
void configureOscillator(void);
void spiDriver(void);
#pragma code main = 0x02
void mainX()
{
	#ifndef __GNUC__
	_asm goto 0x7500 _endasm
	#endif

}

void configureOscillator(void)
{
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF0 = 1;
	
	while(OSCCONbits.IOFS != 1);

}


/**
 * Receive instruction from master to perform read write operation
 */
#pragma code spiDriver = 0x7500
void spiDriver(void)
{
	uint8 data[65] ,command ,rcv_address[3],ID;
	uint32 address ;
	
	LATCbits.LATC0 = 1 ;
	
	configureOscillator();
	while(JumpPin != 1)
	{
		spiReceiveCommand(&command); //Receive command from master

		if (command == Write) //Write Operation
		{
			spiReceiveAddress(rcv_address); //Receive address to write
			address = (uint32)rcv_address[2] << 16 |(uint16) rcv_address[1] << 8 | rcv_address[0] ;
			spiReceiveData(data,64); //Receive data to write
			eraseOneFlashSegment(address/64); //Erase the desired flash segment
			writeOneFlashSegment(address/64,data); //Perform write
			send_1byte(Done); //Tell master jobs done
		}

		else if ( command == Read) //Read Operation
		{	
			spiReceiveAddress(rcv_address); 
			address = (uint32)rcv_address[2] << 16 |(uint16) rcv_address[1] << 8 | rcv_address[0] ;
			copyOneFlashSegment(address/64, data); //Read one flash segment
			sendSegment(data); //Send read segment data to master
		}
		else if (command == DevID) //Read device ID 
		{
			readDevID(&ID); 
			send_1byte(ID); //Send device ID to master
		}

		else if (command == CONFIG) //Configuration Regsiter Write Operation
		{
			spiReceiveAddress(rcv_address);
			address = (uint32)rcv_address[2] << 16 |(uint16) rcv_address[1] << 8 | rcv_address[0] ;
			spiReceiveData(data,1); 
			writeConfiguration(address,data[1]);
		}
	}
	#ifndef __GNUC__
	_asm goto 0x4 _endasm
	#endif
}
