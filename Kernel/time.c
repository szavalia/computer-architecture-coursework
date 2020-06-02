
#include <time.h>
#include <naiveConsole.h>
#include "video_driver.h"

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	printChar('H');	
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void print_secs(){
	if(seconds_elapsed() == 5){
		printChar('!');
		ticks = 0;
	}
	else if(ticks % 18 == 0){
		printChar('.');
	}
}

