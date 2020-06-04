
#include "time.h"
#include "naiveConsole.h"
#include "video_driver.h"

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void printTime(){
	printDec(getHours());
	printS(":");
	printDec(getMinutes());
	printS(":");
	printDec(getSeconds());
}

int * getTime(){
	int time[3]; //hours, minutes, seconds
	time[0] = getHours();
	time[1] = getMinutes();
	time[2] = getSeconds();
	return time;
}
