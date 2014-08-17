#include "unity.h"
#include "p18f4520.h"
#include "Slave.h"
#include "18c.h"
#include "spi.h"
#include "Utils.h"
#include "mock_SegmentHandler.h"
#include "mock_spiSlave.h"
#include "mock_PIC18Flash.h"
#define JumpPin PORTCbits.RC0 
void setUp(void)
{
}

void tearDown(void)
{
}

void test_spiDriver()
{
	//spiDriver();
}
