GLOBAL puts
GLOBAL sum
GLOBAL resta
GLOBAL scanChar

;Acá vamos a poner los llamados al SO para interactuar con el hardware
section .text

;char scanChar(char * destination);

 
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


puts:
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

inforeg:
    push rbp
    mov rbp, rsp

    push r12

    mov r12, 2 ; elegi que este sea el codigo por que era el siguiente en el orden
    int 80h

    pop r12

    mov rsp, rbp
    pop rbp
    ret

; int sum(int num1, int num2)
sum:
    push rbp
    mov rbp, rsp

    add rdi, rsi
    mov rax, rdi

    mov rsp, rbp
    pop rbp
    ret

resta:
    push rbp
    mov rbp, rsp

    sub rdi, rsi
    mov rax, rdi

    mov rsp, rbp
    pop rbp
    ret
        
        
    