GLOBAL cpuVendor
GLOBAL getRAX
GLOBAL getRBX
GLOBAL getRCX

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





