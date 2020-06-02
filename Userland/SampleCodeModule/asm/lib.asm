GLOBAL scanf
GLOBAL puts

;Acá vamos a poner los llamados al SO para interactuar con el hardware
section .text

;char getChar();
getChar:

;char * scanf(char * buf, size_t length) -> rsi = buf, rdi = length
scanf:
    push rbp
    mov rbp, rsp
    
    mov rax, 0        
    int 80h
    
    mov rsp, rbp
    pop rbp
    ret

puts:
    push rbp
    mov rbp, rsp

    mov rax, 1
    int 80h

    mov rsp, rbp
    pop rbp
    ret


        
        
    