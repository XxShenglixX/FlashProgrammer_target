#include <P18F4520.h>
#include "slaveMain.h"
#include "Utils.h"
#include "spiSlave.h"
#include "PIC18Flash.h"
#include "SegmentHandler.h"
#include "spiInfo.h"
#define JumpPin PORTCbits.RC0 
#define Write 0x11
#define Read 0x22
#define CONFIG 0x33
#define DevID 0x44
#define Done 0xFF

#pragma config OSC = INTIO67 , PWRT = ON , WDT = OFF , DEBUG = ON , LVP =OFF
#ifndef __GNUC__
#pragma code main = 0x02
void main()
{
	_asm goto 0x7500 _endasm
}
	#endif

/**
 * Check the status of JumpPin and
 * If 0 , will receive command from master and perform read write operation
 * If 1, will jump to address 0x4 and execute new code
 *
 * 
 */
#pragma code subMain = 0x7500
void subMain(spiInfo info)
{
	LATCbits.LATC0 = 1 ;
	
	configureOscillator();
	

	while(JumpPin != 1)
	{
		commandInterpreter(&info);
	}
	#ifndef __GNUC__
	_asm goto 0x4 _endasm
	#endif
}


/**
 * Configure the slave to run at 4Mhz for quick read write operation
 *
 */
void configureOscillator(void)
{
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF0 = 1;
	
	while(OSCCONbits.IOFS != 1);

}

/**
 * Interpret the command receive from master to react according
 *
 * Input :	info	contains the address,data,ID
 */
void commandInterpreter(spiInfo *info)
{
		uint32 address ;
		spiReceiveCommand(&info->command); //Receive command from master


		if (info->command == Write) //Write Operation
		{
			spiReceiveAddress(info->address); //Receive address to write
			address = (uint32)info->address[2] << 16 |(uint16) info->address[1] << 8 | info->address[0] ;
			spiReceiveData(info->data,64); //Receive data to write
			eraseOneFlashSegment(address/64); //Erase the desired flash segment
			writeOneFlashSegment(address/64,info->data); //Perform write
			send_1byte(Done); //Tell master jobs done
		}

		else if ( info->command == Read) //Read Operation
		{	
			spiReceiveAddress(info->address); 
			address = (uint32)info->address[2] << 16 |(uint16) info->address[1] << 8 | info->address[0] ;
			copyOneFlashSegment(address/64, info->data); //Read one flash segment
			sendSegment(info->data); //Send read segment data to master
		}
		else if (info->command == DevID) //Read device ID 
		{
			readDevID(&info->ID); 
			send_1byte(info->ID); //Send device ID to master
		}

		else if (info->command == CONFIG) //Configuration Register Write Operation
		{
			spiReceiveAddress(info->address);
			address = (uint32)info->address[2] << 16 |(uint16) info->address[1] << 8 | info->address[0] ;
			spiReceiveData(info->data,1); 
			writeConfiguration(address,info->data[0]);
		}



}
