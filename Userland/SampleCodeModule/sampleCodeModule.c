/* sampleCodeModule.c */
#include "usr_lib.h"
#include "calculadora.h"
char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

static char emptyboi[100];
int main() 
{
	puts("dale mabel traeme la calculadora");
	newline();
	launch_calculator();
	//puts("I have decided that I want to die\n");
	putChar('c');
	return 0xDEADC0DE;
}

