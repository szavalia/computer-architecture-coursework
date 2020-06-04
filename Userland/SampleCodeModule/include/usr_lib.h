#ifndef _USR_LIB_H_
#define _USR_LIB_H_
   #include <stdint.h>
   void scanf(char * destination, int length);
   void put(char * source, int length);
   void puts(char * source);
   void scanChar(char * destination);
   void putChar(char c);
   void getTime(int * destination);
   void printTime();
   void getReg(long * regs);
   void inforeg();
   void bootMsg(); //prompt al bootear
   void help();

   void printBase(uint64_t value, uint32_t base);
   void printDec(uint64_t value);
   void printHex(uint64_t value);
   void printBin(uint64_t value);
#endif


