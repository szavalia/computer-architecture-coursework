GLOBAL put
GLOBAL scanChar
GLOBAL getTime
GLOBAL getReg


;Acá vamos a poner los llamados al SO para interactuar con el hardware
section .text

;void scanChar(char * destination); 
 scanChar:
    push rbp
    mov rbp, rsp
    
    push r12
    push r13 

    mov r12, 0
    mov r13, rdi ;puntero a mi char (uno solito)
    int 80h

    pop r13
    pop r12
    
    mov rsp, rbp
    pop rbp
    ret  

;void put(char * source, int size)
put:
    push rbp
    mov rbp, rsp

    push r12
    push r13
    push r15

    mov r12, 1
    mov r13, rdi
    mov r15, rsi
    int 80h

    pop r15
    pop r13
    pop r12

    mov rsp, rbp
    pop rbp
    ret

getReg:
    push rbp
    mov rbp, rsp

    push r12
    push r13

    mov r12, 2 ; elegi que este sea el codigo por que era el siguiente en el orden
    mov r13, rdi
    int 80h

    pop r13
    pop r12

    mov rsp, rbp
    pop rbp
    ret

;void getTime(int * destination) 
getTime:
    push rbp
    mov rbp, rsp

    push r12
    push r13

    mov r12, 3 ; elegi que este sea el codigo por que era el siguiente en el orden
    mov r13, rdi ; le paso un int * para guardar la hora
    int 80h

    pop r13
    pop r12

    mov rsp, rbp
    pop rbp
    ret


        
        
    