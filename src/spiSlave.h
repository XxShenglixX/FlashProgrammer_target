#ifndef spiSlave_H
#define spiSlave_H
#include "Utils.h"

void spiConfigureSlave(void) ;
void spiSendByte(uint8 data);
void spiReadByte(uint8 *rcv_data);


void spiReceiveAddress(uint8* address);
void spiReceiveCommand(uint8* command);
void spiReceiveData(uint8* rcv_data,uint8 count);
void sendSegment(uint8* segment_data);
void send_1byte(uint8 data);
#endif // __SPISLAVE_H