#include <keyboard.h>
#include <naiveConsole.h>
//https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
#define SHIFT 42
#define SHIFT_RELEASE 170
#define CAPSLOCK 0x3A
#define DELETE 0x0E

extern unsigned int getKeyboardScancode(); // viene de keyboard.asm

static char ascode[58][2] = {
{0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'-','+'},{'\b', '\b'},{'\t','\t'},
{'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
{'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
{'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},{'/','?'},{0,0},{0,0},{0,0},{' ',' '}};

static int shift=0, noCaps = 1;

void keyboard_handler(){
    int scanCode = getKeyboardScancode();
    char keyPress = ascode[scanCode][0];
    if(scanCode<58 && 0<=scanCode){
        if(scanCode == SHIFT){
            shift = 1; //apretó shift
        }
        else if(scanCode == DELETE){
            ncBackspace();
        }      
        else if(shift == noCaps){   
            keyPress = ascode[scanCode][1];
        }
        if(keyPress != 0 && scanCode != DELETE){ //para que no imprima las keys no mappeadas
        ncPrintChar(keyPress);
        }
    }
    else{ //no es un caracter mappeado
        if(scanCode == SHIFT_RELEASE){        
            shift = 0;
        }
        else if(scanCode ==  CAPSLOCK){
            noCaps = !noCaps;
        }
    }
}
