GLOBAL cpuVendor
GLOBAL getRAX
GLOBAL getRBX
GLOBAL getRCX
GLOBAL getRDX
GLOBAL getRSI
GLOBAL getRDI
GLOBAL getR12
GLOBAL getR13
GLOBAL getR15


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

;int getRAX();
getRAX:
	ret

getRBX:
	push rbp
	mov rbp, rsp

	mov rax, rbx ;pongo rbx en rax para retornar su contenido 

	mov rsp, rbp
	pop rbp
	ret

getRCX:
	push rbp
	mov rbp, rsp

	mov rax, rcx 

	mov rsp, rbp
	pop rbp
	ret

getRSI:
	push rbp
	mov rbp, rsp

	mov rax, rsi 

	mov rsp, rbp
	pop rbp
	ret

getRDI:
	push rbp
	mov rbp, rsp

	mov rax, rdi 

	mov rsp, rbp
	pop rbp
	ret

getRDX:
	push rbp
	mov rbp, rsp

	mov rax, rdx 

	mov rsp, rbp
	pop rbp
	ret

getR12:
	push rbp
	mov rbp, rsp

	mov rax, r12 

	mov rsp, rbp
	pop rbp
	ret

getR13:
	push rbp
	mov rbp, rsp

	mov rax, r13 

	mov rsp, rbp
	pop rbp
	ret

getR15:
	push rbp
	mov rbp, rsp

	mov rax, r15 

	mov rsp, rbp
	pop rbp
	ret	





