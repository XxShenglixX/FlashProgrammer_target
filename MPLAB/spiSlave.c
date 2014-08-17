#include <P18F4520.h>
#include "spiSlave.h"
#include <spi.h>
#include <delays.h>
#include "Utils.h"
#define ACK 0xA5

/**
  * Receive address from the master for read write operation
  *
  * Input : *address	is the pointer to the location where address is stored
  */
void spiReceiveAddress(uint8* address)
{
	uint8 i ;  

	spiConfigureSlave() ;

	for ( i = 0 ; i < 3 ; i ++)
	{	
		spiReadByte(&(address[i]));
		spiSendByte(ACK);
	}
	
	CloseSPI();
}

/**
  * Receive command from the master to instruct the slave
  *
  * Input : *command	is the pointer to the location where command is stored
  */
void spiReceiveCommand(uint8* command)
{
	uint8 dummy ;

	spiConfigureSlave() ;
	
	spiReadByte(command);
	spiSendByte(ACK);

	CloseSPI();
}

/**
  * Receive an amount of data from master
  *
  * Input : *rcv_data	is the pointer to the location where data is stored
  *	       count 		is the number of data going to be received
  */
void spiReceiveData(uint8* rcv_data,uint8 count)
{
	uint8 dummy,i ;   ;

	spiConfigureSlave() ;

	for ( i = 0 ; i < count ; i ++)
	{	
		spiReadByte(&(rcv_data[i]));
		spiSendByte(ACK);
	}
	
	CloseSPI();
}

/**
  * Send 1 segment to the master
  *
  * Input : *segment_data 	is the pointer to the location containing the data of a segment
  */
void sendSegment(uint8* segment_data)
{
	uint8 dummy,i ;   

	spiConfigureSlave() ;

	for ( i = 0 ; i < 64 ; i ++)
	{	
		spiReadByte(&dummy);
		spiSendByte(segment_data[i]);
	}
	
	CloseSPI();
}


/**
  * Send 1 byte of data to the master and receive a dummy data
  *
  * Input : data	is the value going to be sent out
  */
void send_1byte(uint8 data)
{
	uint8 dummy ;   

	spiConfigureSlave() ;

	spiReadByte(&dummy);
	spiSendByte(data);
	
	CloseSPI();
}



/**
 * Configure SPI in PIC18 as slave
 * SS pin disable
 * Mode (0,1)
 * Input data sampled at middle of data out
 *
 */
void spiConfigureSlave(void)
{
	CloseSPI(); 
	OpenSPI(SLV_SSOFF,MODE_01,SMPMID);

}

/**
  * Send 1 byte of data through spi
  *
  * Input : data	is the data going to be sent out
  */
void spiSendByte(uint8 data)
{
	WriteSPI(data) ;
}

/**
  * Receive 1 byte of data through spi
  *
  * Input : *rcv_data	is the pointer to the location where data is stored
  */
void spiReadByte(uint8 *rcv_data)
{
	*rcv_data = ReadSPI() ;
}
