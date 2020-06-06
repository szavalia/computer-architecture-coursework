#include "usr_lib.h"
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
static char *charBuffer;
static char buffer[65] = { '\0' };


void scanf(char * buffer, int size){
    int  current = 0;
    char * c;
	*c=0;
    while( *c != '\n'){
        scanChar(c);
        if(*c != 0 && current < size){
            buffer[current++] = *c;
        }        
    }
	buffer[current]='\0';
	return;
}

void show_scanf(char * buffer, int size){
    int  current = 0, deletes=0;
    char * c; // hay que resetear;
	*c = 0;
    while( *c != '\n' ){
        scanChar(c);
        if(*c != 0 && current < size){
            buffer[current++] = *c;
			if(*c == '\b'){
				if(current-(deletes+1)>=0){ //para no borrar cosas anteriores
					deletes++;
					putChar(*c);
				}
			}
        }        
    }
	buffer[current]='\0';
	return;
}

void show_processed_scanf(char * buffer, int size){
	int  current = 0;
    char * c; // hay que resetear;
	*c = 0;
    while( *c != '\n' ){
        scanChar(c);
        if(*c != 0 && current < size){
			
			if(' ' <= *c && *c < 127 ){ //es una letra, número o signo de puntuación, '\b' = 127
				putChar(*c);
				buffer[current++] = *c;
			}
			else if(*c == '\t'){
				for(int i=0; i<5;i++){
					buffer[current++] = ' ';
				}
			}
			else if(*c == '\b'){
				if(current>0){ //para no borrar cosas anteriores
					current--;
					putChar(*c);
				}
			}
        }        
    }
	buffer[current]='\0';
	return;
}

void puts(char * string){
	int length = strlen(string);
	put(string, length);
	return;
}

void putChar(char c){
    *charBuffer= c;
    put(charBuffer, 1);
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
	putChar('\n');
	return;
}
void newline(){
	putChar('\n');
}

void inforeg(){ 
	uint64_t regs[16];
	getReg(regs);
	for(int i=0; i<16;i++){
		printDec(i);
		putChar(':');
		printHex(regs[i]);
		putChar('\t');
		putChar('\n');
	}
}

void printmem(uint64_t * dir){ 
	uint64_t bytes[32];
	getMem(dir, bytes);
	putChar('\n');
	for(int i = 0; i < 32; i++){
		printHex(dir+i);
		putChar(':');
		printHex(bytes[i]);
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
	puts("- help: te muestra opciones de ayuda\n");
	puts("- inforeg: luego de presionar Alt + R para guardar los registros, imprime su contenido\n");
	puts("- time: muestra la hora del sistema en formato HH:MM:SS\n");
	puts("- printmem: printea la memoria a partir de la dirección de memoria indicada (separada por un espacio)\n");
	puts("- exit: cierra el programa\n");
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
	if ( l1 != l2){
		return 0;
	}
	int equals = 1;
	for(int i=0; i < min && equals; i++){
		if(s1[i] != s2[i]){
			return 0;
		}
	}
	return 1;
}

void launch_terminal(){ //arreglar!
	char usr_command[100] = { 0 }; //recordar: inicializa todo en 0
	char prompt[] = "$ ";
	//char prompt[] = { '$' , ' ' , 0};
	bootMsg();
	while(1){
		put(prompt, 2);
		show_processed_scanf(usr_command, 100); //no hay comandos más largos que 50 caracteres
		newline();
		puts(usr_command);
		newline();
		if(strcmp(usr_command, "help")){
			help();
		}
		else if(strcmp(usr_command, "time")){
			printTime();
		}
		else if(strcmp(usr_command, "inforeg")){
			inforeg();
		}
		else if(strcmp(usr_command, "printmem")){
			puts("Inserte direccion de memoria:\n");
			printmem(0x400000);			
		}
		else if(strcmp(usr_command, "exit")){
			return;
		}
		else {
			puts("Command not recognized\n");
		}
	}
	return;
}




//--------------------------------------------------------------


void printBase(uint64_t value, uint32_t base)
{
	int digits;
    digits = uintToBase(value, buffer, base);
	put(buffer, digits);
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



static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
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

