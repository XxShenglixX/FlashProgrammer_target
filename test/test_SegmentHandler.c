#include "unity.h"
#include "p18f4520.h"
#include "Utils.h"
#include "mock_PIC18Flash.h"
#include "SegmentHandler.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_eraseOneFlashSegment_given_segment_0_should_return_1_for_OK()
{
	flashEraseSegment_Expect(0);
	TEST_ASSERT_EQUAL(1,eraseOneFlashSegment(0));
}

void test_eraseOneFlashSegment_given_segment_512_should_return_0_for_failure()
{
	TEST_ASSERT_EQUAL(0,eraseOneFlashSegment(512));
}

void test_eraseOneFlashSegment_given_segment_minus_1_should_return_0_for_failure()
{
	TEST_ASSERT_EQUAL(0,eraseOneFlashSegment(-1));
}

void test_writeOneFlashSegment_given_segment_1_should_return_1_for_OK()
{
	uint8 data[64];
	
	flashWrite32Bytes_Expect(64,data,0);
	flashWrite32Bytes_Expect(96,data,32);
	TEST_ASSERT_EQUAL(1,writeOneFlashSegment(1,data));

}

void test_writeOneFlashSegment_given_segment_600_should_return_0_for_failure()
{
	uint8 data[64];
	
	TEST_ASSERT_EQUAL(0,writeOneFlashSegment(600,data));

}

void test_writeOneFlashSegment_given_segment_minus_100_should_return_0_for_failure()
{
	uint8 data[64];
	
	TEST_ASSERT_EQUAL(0,writeOneFlashSegment(-100,data));

}

void test_copyOneFlashSegment_given_segment_511_should_return_1_for_OK()
{
	uint8 data[64];

	flashRead64bytes_Expect(0x7fc0,data); 
	TEST_ASSERT_EQUAL(1,copyOneFlashSegment(511,data));
}

void test_copyOneFlashSegment_given_segment_minus_999_should_return_0_for_failure()
{
	uint8 data[64];

	TEST_ASSERT_EQUAL(0,copyOneFlashSegment(-999,data));
}

void test_copyOneFlashSegment_given_segment_999_should_return_0_for_failure()
{
	uint8 data[64];

	TEST_ASSERT_EQUAL(0,copyOneFlashSegment(999,data));
}