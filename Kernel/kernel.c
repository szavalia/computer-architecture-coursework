#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <video_driver.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	printS("[x64BareBones]");
	newline();

	printS("CPU Vendor:");
	printS(cpuVendor(buffer));
	newline();

	printS("[Loading modules]");
	newline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	printS("[Done]");
	newline();
	newline();

	printS("[Initializing kernel's binary]");
	newline();

	clearBSS(&bss, &endOfKernel - &bss);

	printS("  text: 0x");
	printHex((uint64_t)&text);
	newline();
	printS("  rodata: 0x");
	printHex((uint64_t)&rodata);
	newline();
	printS("  data: 0x");
	printHex((uint64_t)&data);
	newline();
	printS("  bss: 0x");
	printHex((uint64_t)&bss);
	newline();

	printS("[Done]");
	newline();
	newline();
	return getStackBase();
}

extern int getHours();
extern int getMinutes();
extern int getSeconds();

void printTime(){
	printDec(getHours());
	printS(":");
	printDec(getMinutes());
	printS(":");
	printDec(getSeconds());
}

int main()
{	
	/*printS("[Kernel Main]");
	newline();
	printS("  Sample code module at 0x");
	printHex((uint64_t)sampleCodeModuleAddress);
	newline();
	printS("  Calling the sample code module returned: ");
	printHex(((EntryPoint)sampleCodeModuleAddress)());
	newline();
	newline();

	printS("  Sample data module at 0x");
	printHex((uint64_t)sampleDataModuleAddress);
	newline();
	printS("  Sample data module contents: ");
	printS((char*)sampleDataModuleAddress);
	newline();
	printS("[Finished]");
	newline();	*/
	
	load_idt();
	initializeKernelBinary();
	newline();

	printS("Userland main: ");
	newline();
	int (*userlandMain) ();
	userlandMain = sampleCodeModuleAddress;
	int ret = (*userlandMain) ();
	printDec(ret);
	
	/*
	//bandera de boquita
	int blue[] = {255,0,0}, yellow[] = {0,255,255}; 
	for(int i= 0; i<1024;i++){
		for(int j=0; j<768/3;j++){
			writePixel(i,j, blue);
		}
		for(int j=768/3; j<2*768/3;j++){
			writePixel(i,j,yellow);
		}
		for(int j=2*768/3 ; j<768;j++){
			writePixel(i,j,blue);
		}
	}
	*/
	
}


