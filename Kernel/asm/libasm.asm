GLOBAL cpuVendor
GLOBAL getRAX
GLOBAL getRBX
GLOBAL getRCX
GLOBAL getRDX
GLOBAL getRSI
GLOBAL getRDI
GLOBAL getRBP
GLOBAL getRSP
GLOBAL getR8
GLOBAL getR9
GLOBAL getR10
GLOBAL getR11
GLOBAL getR12
GLOBAL getR13
GLOBAL getR14
GLOBAL getR15
GLOBAL memContent

GLOBAL cpuTemperature


section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


cpuTemperature:
	push rbp
	mov rbp, rsp 

	push rbx
	push rcx
	push rdx

	mov rcx, 0
	mov rax, 0

	mov ecx, 0x1A2 ; MSR_TEMPERATURE_TARGET
	rdmsr
	; ahora tengo el resultado en EDX:EAX
	;me interesan los bits 23:16 (target)
	; aparentemente tambien le tengo que sumar el target offset

	mov rdx, 0 ; lo vuelvo a vaciar por las dudas para que no me queden rezagos de antes
	mov edx, eax ; aca voy a poner el offset y despues lo proceso procesarlo

	and eax, 0x00FF0000
	shr eax, 16
	mov rbx, rax

	;proceso offset --> bits 29:24
	and edx, 0x3F000000
	shr edx, 24
	add rbx, rdx

;------Segunda Parte-------
	mov rax, 0
	mov ecx, 0x19C ; IA32_THERM_STATUS 
	rdmsr
	;me interesa el digital readout! bits 22:16


	and eax, 0x007F0000
	shr eax, 16 

	sub rbx, rax ;Target - status
	mov rax, rbx ;pongo la resta en rax para retornarlo 

	pop rdx
	pop rcx
	pop rbx

	mov rsp, rbp
	pop rbp
	ret


;int getRAX();
getRAX:
	ret

getRBX:
	mov rdi, rbx
	call getAux
	ret

getRCX:
	mov rdi, rcx
	call getAux
	ret

getRDX:
	mov rdi, rdx
	call getAux
	ret

getRSI:
	mov rdi, rsi
	call getAux
	ret

getRDI:
	mov rdi, rdi
	call getAux
	ret

getRBP:
	mov rdi, rbp
	call getAux
	ret

getRSP:
	mov rdi, rsp
	call getAux
	ret

getR8:
	mov rdi, r8
	call getAux
	ret

getR9:
	mov rdi, r9
	call getAux
	ret

getR10:
	mov rdi, r10
	call getAux
	ret

getR11:
	mov rdi, r11
	call getAux
	ret

getR12:
	mov rdi, r12
	call getAux
	ret

getR13:
	mov rdi, r13
	call getAux
	ret

getR14:
	mov rdi, r14
	call getAux
	ret
getR15:
	mov rdi, r15
	call getAux
	ret



getAux:
	push rbp
	mov rbp, rsp

	mov rax, rdi

	mov rsp, rbp
	pop rbp
	ret	

memContent:
	push rbp
	mov rbp, rsp

	mov rax, 0 
	mov rbx, rdi ;en rdi deberia tener la posicion de memoria que quiero leer
	mov al, [rbx]

	mov rsp, rbp
	pop rbp
	ret	
	
