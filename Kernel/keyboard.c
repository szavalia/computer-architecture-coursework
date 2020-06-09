#include "keyboard.h"
#include <naiveConsole.h>
#include "video_driver.h"
#include <stdio.h>
#include <stdlib.h>

//https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
#define SHIFT 42
#define SHIFT_RELEASE 170
#define CAPSLOCK 0x3A
#define DELETE 0x0E
#define ENTER 28
#define CHUNK 10
#define LALT 0x38
#define R 0x13
#define P 0x19
#define T 0x14

static char ascode[58][2] = {
{0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','/'},{'8','('},{'9',')'},{'0','='},{'&','_'},{'-','+'},{'\b','\b'},{'\t','\t'},
{'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{'+','*'},
{'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
{'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},{'-','?'},{0,0},{0,0},{0,0},{' ',' '}};

static int flagShift=0, flagNoCaps = 1, buffer_size = 0, left_alt = 0;
static char buffer[1024];
static long regs[16];

extern side;


//capslock y shift!!!
void keyboard_handler(){
    int scanCode = getKeyboardScancode();
    char keyPress = ascode[scanCode][0];

    if(scanCode<59 && 0<=scanCode){
        if(scanCode == SHIFT){
            flagShift = 1; //apretó shift
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
        else if (scanCode == T && left_alt){
            left_alt = 0;
            side = !side;
            if(side == 0){
                newline();
            }
            if(side == 1){
                newlineR();
            }
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




long * getRegs(){
   return regs;
}






