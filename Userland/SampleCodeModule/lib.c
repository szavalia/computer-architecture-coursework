#include "lib.h"


void scanf(char * buffer, int size){
    int  current = 0;
    char * c;
    while( *c != '\n' ){
        scanChar(c);
        if(*c != 0){
            putChar(*c);
            buffer[current++] = *c;
        }        
    }
}

void putChar(char c){
    char * buffer;
    *buffer = c;
    puts(buffer, 1);
}

