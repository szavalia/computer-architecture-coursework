/* sampleCodeModule.c */
#include "usr_lib.h"

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() 
{	char emptyboi[50];
	puts("Holardas\n");
	show_scanf(emptyboi, 50);
	inforeg();
	return 0xDEADC0DE;
}