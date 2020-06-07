GLOBAL cpuVendor
GLOBAL cpuBrand
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


section .text


getRIPAfterInterrupt: 
		push rbp
		mov rbp , rsp

		mov rax , [rsp-8];

		mov rsp , rbp
		pop rbp
		ret


getFLAGSAfterInterrupt:
		push rbp
		mov rbp , rsp

		mov rax, [rsp-24]
		mov rsp , rbp

		pop rbp
		ret

;gwet my fwaggys and reggys back into my cipi
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
			push QWORD[rdi+128]
			push QWORD[rdi+136]
			sub rsp , 4
			mov rdi , [rdi+40]
			popfq
			jmp [rsp+16]
			ret

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx


	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

; char * cpuBrand(char * buffer);
cpuBrand:
	push rbp
	mov rbp , rsp
	push rbx
	push r12
	push r15
	;en rdi tengo mi buffer para cargarle el nombre
	mov eax, 80000000h 
	cpuid
	cmp eax, 80000004h
	jb _Not_Supported
	mov eax, 80000002h
	cpuid

	call _Save_String
	mov eax, 80000003h
	cpuid

	call _Save_String
	mov eax, 80000004h
	cpuid

	call _Save_String

	mov [rdi+1], byte 0
	mov rax, rdi
	sub rax ,49

	mov rsp, rbp
	pop rbp
	ret
	
_Not_Supported:
	ret
	
_Save_String:
	mov [rdi],eax
	mov [rdi+4],ebx
	mov [rdi+8],ecx
	mov [rdi+12],edx
	add rdi, 16
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
	
