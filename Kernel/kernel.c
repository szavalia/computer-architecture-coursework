#include <stdint.h>
#include <string.h>
#include "lib.h"
#include <moduleLoader.h>
//#include <naiveConsole.h>
#include "idtLoader.h"
#include "video_driver.h"
#include "time.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
extern int side = 1;

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
	splitScreen();
	char vendor[13], brand[49];
	printS("[x64BareBones]");
	newline();
	cpuVendor(vendor);
	printS(vendor);
	newline();
	cpuBrand(brand);
	printS(brand);
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
static long initRegs[16];
void saveInitRegs(){
    initRegs[0] = getRAX();
    initRegs[1] = getRBX();
    initRegs[2] = getRCX();
    initRegs[3] = getRDX();
    initRegs[4] = getRSI();
    initRegs[5] = getRDI();
    initRegs[6] = getRBP();
    initRegs[7] = getRSP();
    initRegs[8] = getR8();
    initRegs[9] = getR9();
    initRegs[10] = getR10();
    initRegs[11] = getR11();
    initRegs[12] = getR12();
    initRegs[13] = getR13();
    initRegs[14] = getR14();
    initRegs[15] = getR15();
}

long * getInitRegs(){
   return initRegs;
}



int main()
{	
	load_idt();
	printS("[Kernel Main]");
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
	newline();
	printS("THIS IS THE END!");
	while(1);

}


