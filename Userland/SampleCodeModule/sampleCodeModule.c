/* sampleCodeModule.c */
#include "usr_lib.h"

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	char buffer[20];
	scanf(*buffer, 20);
	put(buffer, 20);
	inforeg();
	//bootMsg();
	return 0;
}