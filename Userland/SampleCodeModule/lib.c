#include "lib.h"


void scanf(char * buffer, int size){
    int  current = 0;
    char * c;
    scanChar(c);
    for(; current < size && (*c != '\n') && (*c != 0) ; current++){
        if(*c != 0){
            buffer[current] = *c;
        }
        scanChar(c);
    }
}

