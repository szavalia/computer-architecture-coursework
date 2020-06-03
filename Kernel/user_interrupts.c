#include "user_interrupts.h"
#include "video_driver.h"
#include "keyboard.h"

//definidas en user_interrupts.asm
extern int getRAX(); //donde se define la interrupción
extern int getRDI(); //primer argumento (buffer)
extern int getRSI(); //segundo argumento (size)


void int80_handler(){
    printS("en int_80handler");
    int option = getR12();
    printS("R12: ");
    printDec(option);
    newline();
    printS("R13: ");
    printHex(getR13());
    newline();
    printS("R15: ");
    printDec(getR15());
    newline();
    switch(option){
        case 0:
            sys_read();
            break;
        case 1:
            sys_write();
            break;
        case 2:
            sys_printReg();
            break;
    }
}

void sys_write(){
    char * buffer = (char *) getR13();
    int size = getR15();
    print(buffer, size);
}
 

 void sys_read(){
    char * c = getR13();
    *c = readChar(); //si no hay nada en el buffer, te retorna un 0    
 }

void sys_printReg(){
    inforeg();
}








