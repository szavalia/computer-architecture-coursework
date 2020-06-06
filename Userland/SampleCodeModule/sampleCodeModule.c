/* sampleCodeModule.c */
#include "usr_lib.h"

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

static emptyboi[20];
int main() 
{	
	char * dir = 0x400000;
	printmem(dir);
	//launch_terminal();
	return 0xDEADC0DE;
}

