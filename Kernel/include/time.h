#ifndef _TIME_H_
#define _TIME_H_

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
int getHours();
int getMinutes();
int getSeconds();
void getTime(int * time);
void printTime();

#endif
