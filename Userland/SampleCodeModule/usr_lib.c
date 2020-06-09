#include "usr_lib.h"
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
static char charBuffer[3072];
static char bufferNum[65] = { '\0' };
static char usr_command[100] = { 0 }; 
void scanf(char * buffer, int size){
    int  current = 0;
    *charBuffer = 0;
    while( *charBuffer != '\n'){
        scanChar(charBuffer);
        if(*charBuffer != 0 && current < size){
            buffer[current++] = *charBuffer;
        }        
    }
	buffer[current]='\0';
	return;
}

void show_scanf(char * buffer, int size){
    int  current = 0, deletes=0;
	*charBuffer = 0;
    while( *charBuffer != '\n' ){
        scanChar(charBuffer);
        if(*charBuffer != 0 && current < size){
            buffer[current++] = *charBuffer;
			if(*charBuffer == '\b'){
				if(current-(deletes+1)>=0){ //para no borrar cosas anteriores
					deletes++;
					putChar(*charBuffer);
				}
			}
        }        
    }
	buffer[current]='\0';
	return;
}

void show_processed_scanf(char * buffer, int size){
	int  current = 0;
	*charBuffer = 0;
    while( *charBuffer != '\n' ){
        scanChar(charBuffer);
        if(*charBuffer != 0 && current < size){
			
			if(' ' <= *charBuffer && *charBuffer < 127 ){ //es una letra, número o signo de puntuación, '\b' = 127
				putChar(*charBuffer);
				buffer[current++] = *charBuffer;
			}
			else if(*charBuffer == '\t'){
				for(int i=0; i<5;i++){
					buffer[current++] = ' ';
				}
			}
			else if(*charBuffer == '\b'){
				if(current>0){ //para no borrar cosas anteriores
					current--;
					putChar(*charBuffer);
				}
			}
        }        
    }
	buffer[current]='\0';
	return;
}

void scanf_for_calculator(char * buffer, int size){
	int  current = 0;
	*charBuffer = 0;
    while( *charBuffer != '=' ){
        scanChar(charBuffer);
        if(*charBuffer != 0 && current < size){
			
			if(' ' <= *charBuffer && *charBuffer < 127 ){ //es una letra, número o signo de puntuación, '\b' = 127
				putChar(*charBuffer);
				buffer[current++] = *charBuffer;
			}
			else if(*charBuffer == '\t'){
				for(int i=0; i<5;i++){
					buffer[current++] = ' ';
				}
			}
			else if(*charBuffer == '\b'){
				if(current>0){ //para no borrar cosas anteriores
					current--;
					putChar(*charBuffer);
				}
			}
        }        
    }
	buffer[current-1]='\0';
	return;
}

void show_numeric_scanf(char * buffer, int size){
	int  current = 0;
	*charBuffer = 0;
	
    while( *charBuffer != '\n' ){
        scanChar(charBuffer);
        if(*charBuffer != 0 && current < size){	
			if('0' <= *charBuffer && *charBuffer <= '9' ){ //es una letra, número o signo de puntuación, '\b' = 127
				putChar(*charBuffer);
				buffer[current++] = *charBuffer;
			}
			else if(*charBuffer == '\b'){
				if(current>0){ //para no borrar cosas anteriores
					current--;
					putChar(*charBuffer);
				}
			}
        }        
    }
	buffer[current]='\0';
	return;
}

uint64_t stringToNum(char * string){
	uint64_t result = 0;
	int length = strlen(string);
	for(int i=0; i<length; i++){
		result = result * 10 + ( string[i] - '0' );
	}
	return result;
}


void puts(char * string){
	int length = strlen(string);
	put(string, length);
	return;
}

void putChar(char c){
    *charBuffer = c;
    put(charBuffer , 1);
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
		printReg((uint64_t)regs[i]);	
		putChar('\n');
	}
}

void printmem(uint8_t * dir){ 
	uint8_t bytes[32];
	getMem(dir, bytes);
	putChar('\n');
	for(int i = 0; i < 32; i++){
		printHex((long) dir+i );
		putChar(':');
		printHex(bytes[i]);
		putChar('\n');
	}

}

void printCPUInfo(){
	char vendor[13], brand[49];
	getCPUInfo(vendor, brand);
	puts("CPU Vendor: ");
	puts(vendor);
	newline();

	puts("CPU Brand: ");
	puts(brand);
	newline();

}

void printTemp(){
	uint64_t temp;
	getTemp(&temp);
	printDec(temp);
	newline();
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
	puts("- printmem: printea 32 bytes a partir de una dirección de memoria\n");
	puts("- cpuinfo: muestra la marca y modelo de la cpu\n");
	puts("- exit: cierra el programa\n");
	puts("- cputemp: muestra la temperatura del procesador\n");
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

int error(){
	return 2/0;
}

void launch_terminal(){ //arreglar!
	
	char memory[20] = { 0 };
	char prompt[] = "$ ";
	int num;
	bootMsg();
	while(1){
		puts("$ ");
		show_processed_scanf(usr_command, 100); //no hay comandos más largos que 50 caracteres
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
			puts("Inserte direccion de memoria (en decimal):\n");
			show_numeric_scanf(memory, 20); 
			uint64_t direc = stringToNum(memory);
			printmem((uint8_t *)direc);	
		}
		else if(strcmp(usr_command, "cpuinfo")){
			printCPUInfo();
		}
		else if(strcmp(usr_command, "error")){
			int num = 2/0;
			error();
		}
		else if(strcmp(usr_command, "exit")){
			return;
		}
		else if(strcmp(usr_command, "cputemp")){
			printTemp();
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
    digits = uintToBase(value, bufferNum, base);
	put(bufferNum, digits);
	return;
}

void printDec(uint64_t value){
    printBase(value, 10);
	return;
}

void printWithDecimals(double value){
	long  ent = parteEntera(value);
	printDec(ent);
	putChar('.');
	value-= ent;
	value *= 10000;
	long deci = parteEntera(value);
	printDec(deci);
}

void printHex(uint64_t value){
    printBase(value, 16);
	return;
}

void printBin(uint64_t value){
    printBase(value, 2);
	return;
}

void printReg(uint64_t value){
	int  digits = uintToBase(value,bufferNum,16);
	digits = 16-digits;
	while((digits--) > 0){
		putChar('0');
	}
	puts(bufferNum);
}

long parteEntera(uint64_t value){
	long rta = 0;
	long mult = 1;
	do{
		uint32_t remainder = value%10;
		rta+=  remainder * mult;
		mult *= 10;
	}
	while(value /= 10);
	return rta;
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

