#include "usr_lib.h"
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

void scanf(char * buffer, int size){
    int  current = 0;
    char * c;
    while( *c != '\n'){
        scanChar(c && current < size);
        if(*c != 0){
            buffer[current++] = *c;
        }        
    }
	return;
}

void show_scanf(char * buffer, int size){
    int  current = 0;
    char * c;
    while( *c != '\n' ){
        scanChar(c);
        if(*c != 0 && current < size){
            putChar(*c);
            buffer[current++] = *c;
        }        
    }
	return;
}

void puts(char * string){
	put(string, strlen(string));
	return;
}

void putChar(char c){
    char * buffer;
    *buffer = c;
    put(buffer, 1);
	return;
}

void printTime(){
    int time[3];
	getTime(time);
	printDec(time[0]); //horas
	putChar(':');
	printDec(time[1]); //minutos
	putChar(':');
	printDec(time[2]); //segundos
	return;
}
void newline(){
	putChar('\n');
}

void inforeg(){ 
	long regs[16];
	getReg(regs);
	/*puts("register information: ");
    newline();
    put("RAX: ",5);
    printDec(regs[0]);
    newline();
    put("RBX: ",5);
    printDec(regs[1]);
    put("RCX: ",5);
    printDec(regs[2]);
    newline();*/
	for(int i=0; i<16;i++){
		printDec(i);
		putChar(':');
		printDec(regs[i]);
		putChar('\n');
	}

}

void bootMsg(){
	char msg[] = "Hello there!\nEstos son los comandos disponibles:\n";
	puts(msg);
	help();
	return;
}

void help(){
	char * msg = "PLACEHOLDER\n";
	puts(msg);
	return;
}

int strlen(char * string){
	int count = 0;
	while(string[count++] != 0);
	return count-1;
}
int strcmp(char * s1, char * s2){
	int l1 = strlen(s1), l2=strlen(s2);
	int min = (l1<l2)? l1 : l2;
	int equals = 1;
	for(int i=0; i < min && equals; i++){
		if(s1[i] != s2[i]){
			equals = 0;
		}
	}
	return equals;
}

void launch_terminal(){ //arreglar!
	char usr_command[50];
	char * commands[3] = {"help", "time", "inforeg"};
	bootMsg();
	char prompt[] = "$ ";
	while(1){
		puts(prompt);
		show_scanf(usr_command, 50); //no hay comandos más largos que 50 caracteres
		if(strcmp(usr_command, "help")){
			help();
		}
		else if(strcmp(usr_command, "time")){
			printTime();
		}
		else if(strcmp(usr_command, "inforeg")){
			inforeg();
		}
		else {
			puts("Command not recognized");
			return;
		}
	}
	return;
}




//--------------------------------------------------------------
static char buffer[64] = { '0' };

void printBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    puts(buffer);
	return;
}

void printDec(uint64_t value){
    printBase(value, 10);
	return;
}

void printHex(uint64_t value){
    printBase(value, 16);
	return;
}

void printBin(uint64_t value){
    printBase(value, 2);
	return;
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

