#GLOBAL putChar
#GLOBAL getChar

;Acá vamos a poner los llamados al SO para interactuar con el hardware
section .text

;char getChar();
getChar:

;char * scanf(char * buf, size_t length) -> rsi = buf, rdi = length
scanf:
    push rbp
    mov rbp, rsp
    
    push rsi

    push rdi
    push rsi

    mov rsi, 0
    pop rdi ; rsi viejo a rdi
    pop rdx ; sdi viejo a rdx

    pop rsi
    
    mov rsp, rbp
    pop rbp


        
        
    