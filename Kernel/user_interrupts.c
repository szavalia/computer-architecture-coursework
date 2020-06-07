#include "user_interrupts.h"
#include "video_driver.h"
#include "keyboard.h"
#include "time.h"
#include "lib.h"


void int80_handler(){
    int option = getR12();
    switch(option){
        case 0:
            sys_read();
            break;
        case 1:
            sys_write();
            break;
        case 2:
            sys_getReg();
            break;
        case 3:
            sys_time();
            break;
        case 4:
            sys_mem();
            break;
        case 5:
            sys_cpuinfo();
            break;
    }
}

void sys_write(){
    char * buffer = (char *) getR13();
    int size = getR15();
    print(buffer, size);
}
 

 void sys_read(){
    char * c = getR13();
    *c = readChar(); //si no hay nada en el buffer, te retorna un 0    
}

void sys_getReg(){
    uint64_t * destination = (uint64_t *) getR13();
    uint64_t * regs =  getRegs();
    for(int i = 0; i < 16; i++){
        destination[i] = regs[i];
    }
}

void sys_time(){
    int * destination = (int *) getR13();  
    int * time = getTime();
    for(int i=0; i<3; i++){ //copio la hora!
        destination[i] = time[i];
    }
}

void sys_mem(){
    uint64_t * destination = (uint64_t *) getR13();
    uint64_t start = (uint64_t *) getR15();
    for(int i = 0; i<32; i++){
        destination[i] = memContent(start+i);
    }
}

void sys_cpuinfo(){
    char * rtaVendor = (char *) getR13();
    char * rtaBrand = (char *) getR15();
    char * vendor, * brand;
    char buffer1[13], buffer2[49];
    vendor = cpuVendor(buffer1);
    brand = cpuBrand(buffer2);

    for(int i=0; i < 13; i++){
        rtaVendor[i] = vendor[i];
    }
    
    for(int i=0; i<49; i++){
        rtaBrand[i] = brand[i];
    }

}







