/* sampleCodeModule.c */
#include "lib.h"

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {

	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	/*//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
	*/
	//char msg[] = "Hola mundo";
	//puts(msg, 10);	
	//puts(msg, 10);
	char buff[20];
	scanf(buff, 20);
	//puts(buff, 20);
	

	return 666;
}