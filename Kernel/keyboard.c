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

static char ascode[58][2] = {
{0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'-','+'},{'\b','\b'},{'\t','\t'},
{'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
{'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
{'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},{'/','?'},{0,0},{0,0},{0,0},{' ',' '}};

static int flagShift=0, flagNoCaps = 1, buffer_size = 0, left_alt = 0;
static char buffer[10];


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
            left_alt = 1;
        }

        if(scanCode == R && left_alt){ //alt + R para inforeg
            saveReg();
            left_alt = 0;
        }
        if(scanCode == P && left_alt){
            inforeg();
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



