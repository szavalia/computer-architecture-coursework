#include "usr_lib.h"
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

void scanf(char * buffer, int size){
    int  current = 0;
    char * c;
    while( *c != '\n' ){
        scanChar(c);
        if(*c != 0){
            putChar(*c);
            buffer[current++] = *c;
        }        
    }
}

void puts(char * string){
    int size=0;
    while(string[size++] != 0);
	put(string, size);
}

void putChar(char c){
    char * buffer;
    *buffer = c;
    put(buffer, 1);
}

void printTime(){
    int time[3];
	getTime(time);
	
	printDec(time[0]); //horas
	putChar(':');
	printDec(time[1]); //minutos
	putChar(':');
	printDec(time[2]); //segundos
}

void bootMsg(){
	char msg[] = "Hello there!\nEstos son los comandos disponibles:\n";
	puts(msg);
	help();
}

void help(){
	char msg[] = "PLACEHOLDER\n";
	puts(msg);
}
//--------------------------------------------------------------
static char buffer[64] = { '0' };

void printBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    puts(buffer);
}

void printDec(uint64_t value){
    printBase(value, 10);
}

void printHex(uint64_t value){
    printBase(value, 16);
}

void printBin(uint64_t value){
    printBase(value, 2);
}


static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

