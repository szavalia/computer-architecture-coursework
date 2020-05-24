#include <time.h>
#include <naiveConsole.h>

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

void print_secs(){
	if(seconds_elapsed() == 5){
		ncPrintChar('!');
		ticks = 0;
	}
	else if(ticks % 18 == 0){
		ncPrintChar('.');
	}
}
