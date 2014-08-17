#ifndef SegmentHandler_H
#define SegmentHandler_H
#include "Utils.h"
uint8 eraseOneFlashSegment(uint16 segmentNumber);
uint8 writeOneFlashSegment(uint16 segmentNumber,uint8 *dataSegment);
uint8 copyOneFlashSegment(uint16 segmentNumber, uint8 *dataSegment);

#endif // SegmentHandler_H
