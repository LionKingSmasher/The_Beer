%define msg_reg  r0
%define size_reg r1

%macro rsa_encrypt 3
	; rax : x
	; r0 : y
	; r1 : N
	; r2 : m
	; r3 : r
	mov rax, %1 
	mov r1, %2
	imul r1, %3
	
%endmacro

global beer_rsa_encrypt

section .bss
result: resq 1

section .data
ras_e: 65537
prime_table: 
	dd 0x02, 0x03, 0x05, 0x07, 0x0a, 0x0c, 0x11, 0x13, 0x17, 0x1c 
	dd 0x1f, 0x25, 0x29, 0x2b, 0x2f, 0x35, 0x3b, 0x3c, 0x43, 0x45

section .text
beer_rsa:
	push rbp
	mov rbp, rsp
	xor r8, r8
	mov qword ptr [rbp - 8], edi  ; char * msg
	mov dword ptr [rbp - 12], esi ; int    size
	mov r0, qword ptr [rbp - 8]
	mov rax, r0
	ret

asm_EEA:
	; r8  : r0
	; r9  : r1
	; r10 : s0
	; r11 : s1
	; r12 : t0
	; r13 : t1
	; r14 : temp
	; r15 : q
	mov r8, rax
	mov r9, rbx
	mov r10, 1
	mov r11, 0
	mov r12, 0
	mov r13, 1
	mov r14, 0
	mov r15, 0

asm_EEA_loop:
	mov eax, r8
	cdq
	idiv r8
	mov r15, eax
	cmp r9, 0
	je asm_EEA_loop