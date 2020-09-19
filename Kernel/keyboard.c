// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "keyboard.h"
#include "video_driver.h"
#include <stdio.h>
#include <stdlib.h>

#define SHIFT 0x2A
#define SHIFT_RELEASE 170
#define CAPSLOCK 0x3A
#define DELETE 0x0E
#define ENTER 28
#define CHUNK 10
#define LALT 0x38
#define R 0x13
#define P 0x19
#define T 0x14
#define BUF_SIZE 1024

static char ascode[59][2] = {
{0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','/'},{'8','('},{'9',')'},{'0','='},{'&','_'},{'-','+'},{'\b','\b'},{'\t','\t'},
{'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{'+','*'},
{'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
{'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},{'-','?'},{0,0},{0,0},{0,0},{' ',' '}, {0,0}};

static int flagShift=0, flagNoCaps = 1, buffer_size = 0, left_alt = 0;
static char buffer[BUF_SIZE]; 
static uint64_t regs[16];
extern int side , context;


void keyboard_handler(){
    int scanCode = getKeyboardScancode();
    char keyPress; //TODO: chequear que quede arreglado 
//TODO: testear el cambio de scanCode<59 -> scanCode<58
    if(scanCode<59 && 0<=scanCode){ 
        keyPress = ascode[scanCode][0];
        if(scanCode == SHIFT){
            flagShift = 1; 
        }
        if(scanCode == CAPSLOCK){
            flagNoCaps = !flagNoCaps;
        }
        if(flagNoCaps == flagShift){
            keyPress = ascode[scanCode][1];
        }
        if (scanCode == LALT){
            left_alt = !left_alt;
        }

        if(scanCode == R && left_alt){ //alt + R para inforeg
            saveRegs();
            left_alt = 0;
        }
        else if (scanCode == T && left_alt && (context == side)){
            left_alt = 0;
            context = 1 - context;
        }
        
        else if(keyPress != 0){ //para que no imprima las keys no mappeadas
        buffer[buffer_size++] = keyPress;
        }
    }
    else if(scanCode == SHIFT_RELEASE){
        flagShift = 0;
    }

}

char readChar(){
    if ( buffer_size == 0 ){
        return 0;
    }
    return buffer[--buffer_size];    
}

void saveRegs(){
    regs[0] = getRAX();
    regs[1] = getRBX();
    regs[2] = getRCX();
    regs[3] = getRDX();
    regs[4] = getRSI();
    regs[5] = getRDI();
    regs[6] = getRBP();
    regs[7] = getRSP();
    regs[8] = getR8();
    regs[9] = getR9();
    regs[10] = getR10();
    regs[11] = getR11();
    regs[12] = getR12();
    regs[13] = getR13();
    regs[14] = getR14();
    regs[15] = getR15();
}

uint64_t * getRegs(){
   return regs;
}






