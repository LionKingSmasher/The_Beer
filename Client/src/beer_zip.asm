%define WIN_BUF   0x80
%define LOOK_BUF  0x7E
%define POINT_BUF WIN_BUF

struc LZ77_t
	.dist : resb 1
	.len  : resb 1
	.data : resb 1
endstruc

struc LZ77_Buffer_t
	.buffer : resb 254
endstruc

section .data
	__point: dd POINT_BUF
	__lz77:
		istruc LZ77_t
			at .dist, db 0
			at .len,  db 0
			at .data, db 0
		iend

global lz77_search
section .text
lz77_search:
	push rbp
	mov rbp, rsp
	xor rax, rax
	
	mov qword [rbp - 8], rdi ; struct LZ77_Buffer_t*
	
	mov rbx, qword [rbp - 8]
	mov rbx, [rbx]
	mov rbx, [rbx + LZ77_Buffer_t.buffer]
	mov bx, byte [rbx + POINT_BUF]
	mov [__lz77 + LZ77_t.data], bx

	mov cx, 0 ; count, i = 0
@1:
	cmp cx, WIN_BUF
	jae done

	mov rdi, qword [rbp - 8]
	mov rdi, [rdi]
	mov rsi, [rdi + LZ77_Buffer_t.buffer]
	mov dx, 0 ; j
@2:
	mov rdi, qword [rbp - 8]
	mov rdi, [rdi]
	mov si, [rdi + LZ77_Buffer_t.buffer + POINT_BUF + cx]

	cmp si, [rdi + LZ77_Buffer_t.buffer + rcx + rdx]
	jmp @1
done:

	mov rax, __lz77

	pop rbp
	ret