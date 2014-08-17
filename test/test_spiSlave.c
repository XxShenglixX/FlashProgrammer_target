#include "unity.h"
#include "p18f4520.h"
#include "18c.h"
#include "mock_spi.h"
#include "Utils.h"
#include "spiSlave.h"


#define Write 0x11
#define Read 0x22
#define CONFIG 0x33
#define DevID 0x44
#define Done 0xFF
#define ACK 0xA5
void setUp(void)
{
}

void tearDown(void)
{
}

void test_spiConfigureSlave_should_call_CloseSPI_and_OpenSPI()
{
	CloseSPI_Expect();
	OpenSPI_Expect(SLV_SSOFF,MODE_01,SMPMID);

	spiConfigureSlave();
}

void test_spiSendByte_should_call_WriteSPI()
{
	WriteSPI_ExpectAndReturn(0x10,0);
	spiSendByte(0x10);
}

void test_spiReadByte_should_call_ReadSPI()
{
	uint8 read ;

	SSPBUF = 0x20;
	ReadSPI_ExpectAndReturn(SSPBUF);
	spiReadByte(&read);
	TEST_ASSERT_EQUAL(0x20,read);
}

void test_send_1byte_should_call_ReadSPI_WriteSPI()
{
	CloseSPI_Expect();
	OpenSPI_Expect(SLV_SSOFF,MODE_01,SMPMID);

	SSPBUF = 0x00;
	ReadSPI_ExpectAndReturn(0x00);
	WriteSPI_ExpectAndReturn(0xAA,0);

	CloseSPI_Expect();

	send_1byte(0xAA);
}


void test_spiReceiveCommand_given_command_Write_should_return_Write_to_command()
{
	uint8 command ;

	CloseSPI_Expect();
	OpenSPI_Expect(SLV_SSOFF,MODE_01,SMPMID);

	SSPBUF = Write;
	ReadSPI_ExpectAndReturn(Write);
	WriteSPI_ExpectAndReturn(ACK,0);

	CloseSPI_Expect();

	spiReceiveCommand(&command);
	TEST_ASSERT_EQUAL(Write,command);
}

void test_spiReceiveAddress_given_0x10_0x11_0x22_should_return_address_to_addressArray()
{
	uint8 addressArray[3];

	CloseSPI_Expect();
	OpenSPI_Expect(SLV_SSOFF,MODE_01,SMPMID);

	SSPBUF = 0x10;
	ReadSPI_ExpectAndReturn(0x10);
	WriteSPI_ExpectAndReturn(ACK,0);

	SSPBUF = 0x11;
	ReadSPI_ExpectAndReturn(0x11);
	WriteSPI_ExpectAndReturn(ACK,0);

	SSPBUF = 0x12;
	ReadSPI_ExpectAndReturn(0x12);
	WriteSPI_ExpectAndReturn(ACK,0);

	CloseSPI_Expect();
	spiReceiveAddress(addressArray);
	TEST_ASSERT_EQUAL(0x10,addressArray[0]);
	TEST_ASSERT_EQUAL(0x11,addressArray[1]);
	TEST_ASSERT_EQUAL(0x12,addressArray[2]);

}


void test_spiReceiveData_given_count_0_should_receive_nothing()
{
	uint8 data[64] = {1};

	CloseSPI_Expect();
	OpenSPI_Expect(SLV_SSOFF,MODE_01,SMPMID);

	CloseSPI_Expect();

	spiReceiveData(data,0);
	TEST_ASSERT_EQUAL(1,data[0]);
}

void test_spiReceiveData_given_count_2_should_return_data_to_array()
{
	uint8 data[64] = {1};

	CloseSPI_Expect();
	OpenSPI_Expect(SLV_SSOFF,MODE_01,SMPMID);

	SSPBUF = 0xAA;
	ReadSPI_ExpectAndReturn(0xAA);
	WriteSPI_ExpectAndReturn(ACK,0);

	SSPBUF = 0xBB;
	ReadSPI_ExpectAndReturn(0xBB);
	WriteSPI_ExpectAndReturn(ACK,0);


	CloseSPI_Expect();

	spiReceiveData(data,2);
	TEST_ASSERT_EQUAL(0xAA,data[0]);
	TEST_ASSERT_EQUAL(0xBB,data[1]);

}


