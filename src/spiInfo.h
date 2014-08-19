#ifndef spiInfo_H
#define spiInfo_H
#include "Utils.h"

typedef struct
{
	uint8 data[64];
	uint8 command ;
	uint8 address[3] ;
	uint8 ID;
}spiInfo ;
#endif // spiInfo_H
