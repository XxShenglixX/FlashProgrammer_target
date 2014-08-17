#ifndef PIC18Flash_H
#define PIC18Flash_H
#include "Utils.h"

void flashEraseSegment(uint16 segmentToErase);
void flashWrite32Bytes(uint16 addressToWrite,uint8 *data,uint8 dataStartPoint);
void flashRead64bytes(uint16 addressToRead,uint8 *data);

void writeConfiguration(uint32 addressToWrite, uint8 data);
void readDevID(uint8 *data);
#endif // PIC18Flash_H
