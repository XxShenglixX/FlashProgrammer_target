#include "18c.h"
#include "PIC18Flash.h"
#include "Utils.h"

/**
 * 1 segment means 64 bytes of flash memory
 * 
 * Input : segmentToErase choose the segment of flash memory to erase 
 *
 **/
void flashEraseSegment(uint16 segmentToErase)
{
		TBLPTR = segmentToErase * 64 ;
		EECON1 = 0x94 ;// Access flash program memory ,allow write to flash , enable flash row erase
		INTCONbits.GIE = 0; // Disable interrupt
		/*Special Requirement */
		EECON2 = 0x55;
		EECON2 = 0xAA;
		EECON1bits.WR = 1 ; // Initiate program memory erase/write cycle 
	
}

/**
 * Write 32 bytes of data to flash memory
 *
 *  Input : addressToWrite is the desired address of the  flash memory to perform write operation
 * 	       data contain the address of the data to be written
 *
 **/
void flashWrite32Bytes(uint16 addressToWrite,uint8 *data,uint8 dataStartPoint)
{
	uint8 i, j = dataStartPoint ;
 	
		TBLPTR = addressToWrite ;
		for ( i = 0 ; i < 32 ; i ++)
		{
			TABLAT = data[j] ;
			#ifdef __GNUC__
			#else
			_asm TBLWTPOSTINC _endasm
			#endif
			j++;
		}

		EECON1 = 0x84 ;// Access flash program memory ,allow write to flash
		INTCONbits.GIE = 0; // Disable interrupt
	
		TBLPTR = addressToWrite ; // Reload table pointer to desired location
		/*Special Requirement */
		EECON2 = 0x55;
		EECON2 = 0xAA;
		EECON1bits.WR = 1 ; // Initiate program memory erase/write cycle 
	
		EECON1bits.WREN = 0 ; // Disable write 
}

/**
 * Read 64 bytes from the flash memory
 *
 *  Input : addressToRead is the desired address of the flash memory to read 
 *	       data contains the address that store the information read
 *
 * Output : return the information read from the flash memory
 *
 **/
void flashRead64bytes(uint16 addressToRead,uint8 *data)
{
	char i ;

		TBLPTR = addressToRead ;
		for ( i = 0 ; i < 63 ; i++ )
		{
			#ifdef __GNUC__
			#else
			_asm TBLRDPOSTINC _endasm 
			#endif
			data[i] = TABLAT ;
		}
}

/**
 * Program configuration register of PIC
 *
 *  Input : addressToWrite is the desired address of the  flash memory to perform write operation
 * 	       data contain the address of the data to be written
*	       count indicate how many configuration register to be written
 *
 **/
void writeConfiguration(uint32 addressToWrite, uint8 data)
{
	char i = 0 ;
	TBLPTR = addressToWrite ;

	TABLAT = data ;
	#ifdef __GNUC__
	#else
	_asm TBLWTPOSTINC _endasm
	#endif
	

	EECON1 = 0x84 ;// Access flash program memory ,allow write to flash
	INTCONbits.GIE = 0; // Disable interrupt
	
	TBLPTR = addressToWrite ; // Reload table pointer to desired location
	/*Special Requirement */
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1 ; // Initiate program memory erase/write cycle 
	
	EECON1bits.WREN = 0 ; // Disable write 
}

/**
 * Read device ID of PIC
 *
 *  Input : data is the pointer to where the ID is read and stored
 **/
void readDevID(uint8 *data)
{
	TBLPTR = 0x3FFFFF ;
	#ifdef __GNUC__
	#else
	_asm TBLRD _endasm 
	#endif
	*data = TABLAT;
}