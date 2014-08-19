# MPLAB IDE generated this makefile for use with GNU make.
# Project: main.mcp
# Date: Mon Aug 18 15:53:35 2014

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

main.cof : PIC18Flash.o slaveMain.o spiSlave.o c018i.o SegmentHandler.o
	$(LD) /p18F4520 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "..\Project\LKR\18f4520_g.lkr" "PIC18Flash.o" "slaveMain.o" "spiSlave.o" "c018i.o" "SegmentHandler.o" /u_CRUNTIME /u_DEBUG /u_DEBUGCODESTART=0x7dc0 /u_DEBUGCODELEN=0x240 /u_DEBUGDATASTART=0x5f6 /u_DEBUGDATALEN=0xa /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /z__MPLAB_DEBUGGER_ICD3=1 /z__ICD2RAM=1 /o"main.cof" /M"main.map" /W

PIC18Flash.o : PIC18Flash.c PIC18Flash.h PIC18Flash.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/P18F4520.h Utils.h
	$(CC) -p=18F4520 "PIC18Flash.c" -fo="PIC18Flash.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

slaveMain.o : slaveMain.c spiSlave.h PIC18Flash.h SegmentHandler.h slaveMain.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/P18F4520.h Utils.h
	$(CC) -p=18F4520 "slaveMain.c" -fo="slaveMain.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

spiSlave.o : spiSlave.c spiSlave.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/spi.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/delays.h spiSlave.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/P18F4520.h Utils.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/pconfig.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18cxxx.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f4520.h
	$(CC) -p=18F4520 "spiSlave.c" -fo="spiSlave.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

c018i.o : ../Project/c018i.c
	$(CC) -p=18F4520 "C:\Users\Shengli\Desktop\Project\c018i.c" -fo="c018i.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

SegmentHandler.o : SegmentHandler.c SegmentHandler.h PIC18Flash.h SegmentHandler.c Utils.h
	$(CC) -p=18F4520 "SegmentHandler.c" -fo="SegmentHandler.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "PIC18Flash.o" "slaveMain.o" "spiSlave.o" "c018i.o" "SegmentHandler.o" "main.cof" "main.hex"

