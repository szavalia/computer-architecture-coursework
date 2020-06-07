

void exceptionDispatcher(uint64_t exception){
    switch(exception){
        case 0:
            cero_division();
            break;
        case 6:
            invalid_opcode();
            break;
    }
    return;
}

void cero_division(){

}

void invalid_opcode(){
    
}