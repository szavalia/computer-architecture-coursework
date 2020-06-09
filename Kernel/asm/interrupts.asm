
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt


GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _irq60Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler
GLOBAL getRIP

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN getInitRegs
EXTERN main


SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	push rax 
	mov  rax ,[rsp+8] ; preservo el RIP
	mov [ripaux], rax ; guardo el RIP en una var auxiliar
	pop rax

	pushState
	mov rdi, %1 ; pasaje de parametro
	
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
	
	popState
	
	;call swap_context

	iretq
%endmacro



%macro exceptionHandler 1
	push rax 
	mov  rax ,[rsp+8] ; recupero el RIP
	mov [ripaux], rax ; guardo el RIP en una var auxiliar
	pop rax

	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState

	mov QWORD[rsp], 400000h ; sampleCodeModuleAddress en el último lugar del stack (donde guardo el ip)
	mov rbp, 10DFF8h ; llevo el rbp al principio del stack (me arruina el return)	


	iretq
	

%endmacro

getRIP:	
	mov rax, ripaux
	ret
	
_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

;int 80h
_irq60Handler:
	irqHandlerMaster 60


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid opcode exception
_exception6Handler:
	exceptionHandler 6


haltcpu:
	cli
	hlt
	ret

	;void restoreCpu( long * regs )
restoreCpu:
			mov rax , [rdi]
			mov rbx , [rdi+8]
			mov rcx , [rdi+16]
			mov rdx , [rdi+24]
			mov rsi , [rdi+32]
			;mov rdi , [rdi+40]
			mov rbp , [rdi+48]
			mov rsp , [rdi+56]
			mov r8  , [rdi+64]
			mov r9  , [rdi+72]
			mov r10 , [rdi+80]
			mov r11 , [rdi+88]
			mov r12 , [rdi+96]
			mov r13 , [rdi+104]
			mov r14 , [rdi+112]
			mov r15 , [rdi+120]
			mov rdi , [rdi+40]
			ret


SECTION .bss
	aux resq 1
	ripaux resb 8