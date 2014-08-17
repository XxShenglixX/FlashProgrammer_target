#include "SegmentHandler.h"
#include "Utils.h"
#include "PIC18Flash.h"


/**
 * Erase 1 flash segment *1 segment is 64 bytes*
 *
 *	Input : segmentNumber  is the number of segment going to be erased
 *
 * Output : 1 for OK / success
 *          0 for failure / error
 */
uint8 eraseOneFlashSegment(uint16 segmentNumber)
{
	if (segmentNumber > 511 || segmentNumber < 0 )
		return 0 ;
		
	flashEraseSegment(segmentNumber);
	
	return 1 ;
}


/**
 * Write 1 flash segment *1 segment is 64 bytes*
 *
 *	Input : segmentNumber	contain the number of segment going to be written with data
 *			dataSegment		contain the up to date data 
 *
 * Output : 1 for OK / success
 *          0 for failure / error
 */
uint8 writeOneFlashSegment(uint16 segmentNumber,uint8 *dataSegment)
{
	if (segmentNumber > 511 || segmentNumber < 0 )
		return 0 ;
		
	flashWrite32Bytes( (segmentNumber * 64), dataSegment,0 );
	flashWrite32Bytes( (segmentNumber *64)+32, dataSegment,32);
	
	return 1 ;
}



/**
 * Read 64 bytes of data from 1 flash segment *1 segment is 64 bytes*
 *
 *	Input : segmentNumber  is the number of segment going to be read
 *			dataSegment	   contain address to store the data read
 *
 * Output : 1 for OK / success
 *          0 for failure / error
 */
uint8 copyOneFlashSegment(uint16 segmentNumber, uint8 *dataSegment)
{
	if (segmentNumber > 511 || segmentNumber < 0 )
		return 0 ;
		
	flashRead64bytes( (segmentNumber * 64) , dataSegment); 
	return 1 ;
}

