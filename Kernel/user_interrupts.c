#include "user_interrupts.h"
#include "video_driver.h"
#include "keyboard.h"

extern int getRAX(); //definidas en user_interrupts.asm
extern int getRBX();
extern int getRCX();

void int80_handler(){
    int option = getRAX();
    switch(option){
        case 0:
            sys_read();
            break;
        case 1:
            sys_write();
            break;
    }
}

void sys_write(){
    char * buffer = getRBX();
    size_t size = getRCX();
    print(buffer, size);
}

void sys_read(){
    char * buffer = getRBX();
    size_t size = getRCX();
    int count = 0;
    char aux;
    while(count <= size && (aux = readChar()) != '\n'){
        buffer[count++]=aux;
    }
}