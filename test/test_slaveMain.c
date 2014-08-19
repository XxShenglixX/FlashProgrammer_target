#include "unity.h"
#include "p18f4520.h"
#include "slaveMain.h"
#include "18c.h"
#include "Utils.h"
#include "spiInfo.h"
#include "mock_SegmentHandler.h"
#include "mock_spiSlave.h"
#include "mock_PIC18Flash.h"
#define JumpPin PORTCbits.RC0 
#define Write 0x11
#define Read 0x22
#define CONFIG 0x33
#define DevID 0x44
#define Done 0xFF

void setUp(void)
{
}

void tearDown(void)
{
}

void test_commandInterpreter_given_receive_command_read_should_call_spiReceiveAddress_copyOneFlashSegment_and_sendSegment()
{
	spiInfo info;
	
	spiReceiveCommand_Expect(&info.command);
	info.command = Read;
	
	spiReceiveAddress_Expect(info.address);
	info.address[0] = 0x80 ;
	info.address[1] = 0x02;
	info.address[2] = 0x00 ;
	
	copyOneFlashSegment_ExpectAndReturn(10, info.data,1); 
	sendSegment_Expect(info.data);

	commandInterpreter(&info);
	
}


 void test_commandInterpreter_given_receive_command_write_should_call_spiReceiveAddress_spiReceiveData_eraseOneFlashSegment_writeOneFlashSegment_send_1byte()
{
	spiInfo info;
	
	spiReceiveCommand_Expect(&info.command);
	info.command = Write;
	
	spiReceiveAddress_Expect(info.address);
	info.address[0] = 0x80 ;
	info.address[1] = 0x02;
	info.address[2] = 0x00 ;
	
	spiReceiveData_Expect(info.data,64);
	eraseOneFlashSegment_ExpectAndReturn(10,1);
	writeOneFlashSegment_ExpectAndReturn(10,info.data,1);
	send_1byte_Expect(Done);
	
	commandInterpreter(&info);
} 

 void test_commandInterpreter_given_receive_command_DevID_should_call_readDevID_send_1byte()
{
	spiInfo info;
	
	spiReceiveCommand_Expect(&info.command);
	info.command = DevID;
	
	readDevID_Expect(&info.ID);
	send_1byte_Expect(info.ID);
	
	commandInterpreter(&info);
} 


 void test_commandInterpreter_given_receive_command_CONFIG_should_call_spiReceiveAddress_spiReceiveData_writeConfiguration()
{
	spiInfo info;
	
	spiReceiveCommand_Expect(&info.command);
	info.command = CONFIG;
	
	spiReceiveAddress_Expect(info.address);
	info.address[0] = 0x00 ;
	info.address[1] = 0x00;
	info.address[2] = 0x30 ;
	
	spiReceiveData_Expect(info.data,1);
	writeConfiguration_Expect(0x300000,info.data[0]);
	
	commandInterpreter(&info);
} 
