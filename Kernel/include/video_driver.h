
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
void splitScreen();
void toStartOfLine();
void scroll();
void printRegs();

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void printBase(uint64_t value, uint32_t base);
void printDec(uint64_t value);
void printHex(uint64_t value);
void printBin(uint64_t value);


#endif
