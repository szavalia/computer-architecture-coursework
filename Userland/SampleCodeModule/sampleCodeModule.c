/* sampleCodeModule.c */
#include "usr_lib.h"
#include "calculadora.h"

extern void getContext(int * context);

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
		changeContext();

	}
	while(1);
	
	

	
	//puts("I have decided that I want to die\n");
	return 0xDEADC0DE;
}

