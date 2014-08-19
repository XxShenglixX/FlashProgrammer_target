#ifndef slaveMain_H
#define slaveMain_H

#include "spiInfo.h"
void configureOscillator(void);
void commandInterpreter(spiInfo *info);
void subMain(spiInfo info);

#endif // slaveMain_H
