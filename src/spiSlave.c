#include "18c.h"
#include "spiSlave.h"
#include <spi.h>
#include <delays.h>
#include "Utils.h"
#define ACK 0xA5

/**
 * Receive command from master through spi
 *
 *
 * Input 	: command	is the pointer to the place where command is stored
 *
 *
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
 * Receive address to perform read write from master
 *
 * Input : address	is the pointer to where address is stored
 *
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
 * Receive data to be written into the flash from master
 *
 * Input :	data	is the pointer to where data is stored
 *			count	is the amount of data to be received 
 *
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
 * Send 1 segment read to the master
 *
 * Input :	segment_data	is the pointer to where the segment data is stored
 *
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
 * Send 1 byte of data to the master (For sending write status and device ID purpose)
 *
 * Input :	data	is the data going to be sent out
 *
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
 *
 * SS pin disable
 * Mode (0,1)
 * Input data sampled at middle of data out
 */
void spiConfigureSlave(void)
{
	CloseSPI();
	OpenSPI(SLV_SSOFF,MODE_01,SMPMID);

}

/**
 * Send a byte of data through spi
 *
 * Input : data is the data going to be sent out
 *
 */
void spiSendByte(uint8 data)
{
	WriteSPI(data) ;
}

/**
 * Receive a byte of data through spi 
 *
 * Input : rcv_data	is the pointer to the place where data is stored
 *
 */
void spiReadByte(uint8 *rcv_data)
{
	*rcv_data = ReadSPI() ;

}
