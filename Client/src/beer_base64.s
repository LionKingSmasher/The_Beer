global beer_base64

section .bss
base64_res: resb 1024

section .data
base64_table:
	db "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
section .text

beer_base64:
	push rbp

	mov rbp, rsp

	xor r9, r9
	xor r13, r13

	mov qword [rbp - 8], rdi  ; void *
	mov dword [rbp - 12], esi ; int size

	mov eax, dword [rbp - 12]
	mov ecx, 3
	cdq
	idiv ecx

	; cmp edx, 0
	; je start_encode
	; inc eax

start_encode:
	mov ecx, eax
	mov rdx, qword [rbp - 8]
	; lea r10, [base64_res]
do_put_3_char:
	cmp r13, rcx
	jae done
	call put_3_chars
	
	mov r11, rbx
	shr ebx, 18
	mov al, [base64_table + ebx]
	mov byte [base64_res + r9 * 4], al

	xor rdi, rdi

	call put_4_result
	jmp do_put_3_char

done:
	mov byte [base64_res + r9 * 4 + 1], 0x00
	lea rax, [base64_res]

	pop rbp
	ret

put_3_chars:
	mov rdi, rdx
	lea rdx, [rdi + 4 * r13]
	mov byte bl, [rdx]
	shl ebx, 8
	lea rdx, [rdi + 4 * r13 + 1]
	mov byte bl, [rdx]
	shl ebx, 8
	lea rdx, [rdi + 4 * r13 + 2]
	mov byte bl, [rdx]
	inc r13
	mov rdx, rdi
	ret

put_4_result:

	mov rbx, r11
	shr ebx, 12
	and ebx, 0x3f
	mov al, [base64_table + ebx]
	mov byte [base64_res + r9 * 4 + 1], al

	mov rbx, r11
	shr ebx, 6
	and ebx, 0x3f
	mov al, [base64_table + ebx]
	mov byte [base64_res + r9 * 4 + 2], al

	mov rbx, r11
	shr ebx, 0
	and ebx, 0x3f
	mov al, [base64_table + ebx]
	mov byte [base64_res + r9 * 4 + 3], al

	inc r9
	ret
