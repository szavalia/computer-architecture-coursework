/* sampleCodeModule.c */
#include "usr_lib.h"
#include "calculadora.h"
char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

static char option[100];
static int context[1];
int main() 
{
	
	do{
		getContext(context);
		if(*context==0){
			launch_terminal();
		}
		else if(*context == 1){
			launch_calculator();
		}	

	}
	while(1);
	
	

	
	//puts("I have decided that I want to die\n");
	return 0xDEADC0DE;
}

