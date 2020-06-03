#include "user_interrupts.h"
#include "video_driver.h"
#include "keyboard.h"
#include <stdio.h>

//definidas en user_interrupts.asm
extern int getRAX(); //donde se define la interrupción
extern int getRDI(); //primer argumento (buffer)
extern int getRSI(); //segundo argumento (size)


void int80_handler(){
    int option = getR12();
    printS("En int80_handler, RAX vale: ");
    printDec(option);
    newline();
    printHex(getR13());
    newline();
    printDec(getR15());
    newline();
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
    printS("En sys_write!");
    newline();
    char * buffer = (char *) getR13();
    printS("Mensaje: ");
    print(buffer, 10);
    newline();
    int size = getR15();
    printDec(size);
    newline();
    printS("Ahora hacemos el print posta");
    newline();
    print(buffer, size);
}
 
void sys_read(){
    char * buffer = (char *)getRDI();
    int size = getRSI();
    int count = 0;
    char aux=readChar();
    int beginning = get_buffer_size();
    while(count < size && (aux=readChar()) != '\n'){
        printChar(aux);
        buffer[count++] = aux;
    }
    //stdin_read(buffer, beginning, beginning + length); //levantá el largo deseado, creo que es al pedo si lo vas copiando en el while
    freebuffer(beginning); //borrá todo lo que se escribió

}
    /*
    1) abro un prompt
    2) cada vez que pone una tecla, la muestro en pantalla
    3) cuando la tecla sea '\n', cierro el prompt
    4) leo size caracteres de lo que queda en el buffer de teckado
    */

    /*while(count <= size && (aux = readChar()) != '\n'){
        buffer[count++]=aux;}
    }*/

