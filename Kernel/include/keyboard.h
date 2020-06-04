#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
extern unsigned int getKeyboardScancode(); // viene de keyboard.asm
void keyboard_handler();
char readChar();
void freebuffer(int beginning);
int get_buffer_size();
void saveRegs();
long * getRegs();
#endif