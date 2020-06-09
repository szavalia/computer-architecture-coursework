/* sampleCodeModule.c */
#include "usr_lib.h"
#include "calculadora.h"
char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

static char emptyboi[100];
int main() 
{	
	long ans2;	
	double answer;
	int flag = 0;
	while (  flag == 0 ){
		show_processed_scanf(emptyboi,100);
		flag = calculate(emptyboi,&answer);
		long ans2 = (long) answer;
		printDec(ans2);
		putChar('\n');
		puts("Y el flag dio:");
		printDec((long) flag);
		putChar('\n');
	}
	
	//puts("I have decided that I want to die\n");
	putChar('c');
	return 0xDEADC0DE;
}

