#ifndef _VIDEO_DRIVER_H_
#define _VIDEO_DRIVER_H_
void writePixel( int x, int y, int * colour );
void newLine();
void printS(const char * string);
void backspace();
void printChar(char c);
/*  H 
void PrintBase(uint64_t value, uint32_t base);
void printDec(uint64_t value);
void printHex(uint64_t value);
void PrintBin(uint64_t value);
*/
#endif