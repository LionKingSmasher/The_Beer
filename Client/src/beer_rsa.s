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

; section .bss
; result: resq 1

section .data
prime_table: 
	dd 0x02, 0x03, 0x05, 0x07, 0x0a, 0x0c, 0x11, 0x13, 0x17, 0x1c 
	dd 0x1f, 0x25, 0x29, 0x2b, 0x2f, 0x35, 0x3b, 0x3c, 0x43, 0x45

section .text
beer_rsa:
	push rbp
	mov rbp, rsp
	mov qword ptr [rbp - 8], edi  ; char * msg
	mov dword ptr [rbp - 12], esi ; int    size
	mov r0, qword ptr [rbp - 8]
	mov rax, r0
	ret