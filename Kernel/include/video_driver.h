
#ifndef _VIDEO_DRIVER_H_
#define _VIDEO_DRIVER_H_
#include <stdint.h>
long getFrameBuffer();
void writePixel( int x, int y, int * colour );
void newline();
void writePixel( int x, int y, int * colour );
void newline();
void writePixel( int x, int y, int * colour );
void newline();
void printS(const char * string);
void backspace();
void printChar(char c);
void print(const char * string, int size);
void clear();
void vendor();
void temp();
//void toStartOfLine();

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void printBase(uint64_t value, uint32_t base);
void printDec(uint64_t value);
void printHex(uint64_t value);
void printBin(uint64_t value);

//Get registros
long getRAX();
long getRBX();
long getRCX();
long getRDX();
long getRSI();
long getRDI();
long getRBP();
long getRSP();
long getR8();
long getR9();
long getR10();
long getR11();
long getR12();
long getR13();
long getR14();
long getR15();
#endif
