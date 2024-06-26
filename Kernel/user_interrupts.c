// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
        case 6:
            sys_temp();
            break;
        case 7:
            sys_context();
            break;
        case 8:
            sys_update_context();
            break;
    }
}

void sys_write(){
    char * buffer = (char *) getR13();
    int size = getR15();
    print(buffer, size);
}
 

 void sys_read(){
    char * c = (char *) getR13();
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
    int time[3];
    getTime(time);
    for(int i=0; i<3; i++){ //copio la hora!
        destination[i] = time[i];
    }
}

void sys_mem(){
    uint8_t * destination = (uint8_t *) getR13();
    uint8_t * start = (uint8_t *) getR15();
    for(int i = 0; i<32; i++){ //TODO: verificar este cambio a uint8_t
        destination[i] = memContent(start+i);
    }
}

void sys_cpuinfo(){
    char * rtaVendor = (char *) getR13();
    char * rtaBrand = (char *) getR15();
    char buffer1[13], buffer2[49];
    cpuVendor(buffer1);
    cpuBrand(buffer2);

    for(int i=0; i < 13; i++){
        rtaVendor[i] = buffer1[i];
    }
    
    for(int i=0; i<49; i++){
        rtaBrand[i] = buffer2[i];
    }

}

void sys_temp(){
    uint64_t * rta = (uint64_t *) getR13();
    rta[0] = cpuTemperature();
}

void sys_context(){
    int * rta = (int *) getR13();
    *rta = getContext();
}

void sys_update_context(){
    changeContext();
}





