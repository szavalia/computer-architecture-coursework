#ifndef __USER_INTERRUPTS_H__
#define __USER_INTERRUPTS_H__
#include <stdint.h>
void int80_handler();

void sys_write();
void sys_read();
void sys_getReg();
void sys_time();

#endif