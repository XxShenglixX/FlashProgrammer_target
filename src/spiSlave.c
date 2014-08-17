#include <P18F4520.h>
#include "spiSlave.h"
#include <spi.h>
#include <delays.h>
#include "Utils.h"
#define ACK 0xA5


void spiReceiveCommand(uint8* command)
{
	uint8 dummy ;

	spiConfigureSlave() ;

	spiReadByte(command);
	spiSendByte(ACK);

	CloseSPI();
}

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

void spiSendByte(uint8 data)
{
	WriteSPI(data) ;
}

void spiReadByte(uint8 *rcv_data)
{
	*rcv_data = ReadSPI() ;

}
