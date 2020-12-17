	
; Author: Meetesh Kalpesh Mehta
; Compiler Name: XOPE
; year: 2020
; version: 0.4.2 
; changes:; 1) If else bridging
; 2) Fix infinite loop possibility in Loop
; 3) Semi-conditional Break statement for Loops
; 4) 4) Added support for comments
; comment: Refactoring the code
	
section .bss
integer_buffer resb 100

section .data
userInputData times 8 db 0
newLine db 10
variables times 27 dq 0
printText times 200 db 0

_printRAX:
; leaving other registers unmodified
push rbx
push rcx
push rdi

mov rcx, integer_buffer ; digit space
mov rdi, 0 ; calculate offset

_printRAXLoop1:
mov rdx, 0 ; do this before division, said the gods
mov rbx, 10
div rbx ; divide by 10, for the remainder of course
push rax
add rdx, 48 ; add 48 to remainder, ascii conversion
mov [rcx], dl ; store 8 bit value in the buffer
inc rcx ; point to next address
inc rdi ; increment offset
pop rax

cmp rax, 0
jne _printRAXLoop1

_printRAXLoop2:
mov rcx, integer_buffer
add rcx, rdi

push rdi

mov rax, 1
mov rdi, 1
mov rsi, rcx
mov rdx, 1
syscall

pop rdi

dec rdi

cmp rdi, 0
jge _printRAXLoop2

pop rdi
pop rcx
pop rbx

ret

_printText:
mov rax, 1
mov rdi, 1
mov rsi, printText
syscall
ret

_getInputInteger:
call _getInput
call _parseInt
ret

_getInput:
mov rax, 0
mov rdi, 0
mov rsi, userInputData
mov rdx, 8
syscall
ret

_parseInt:
; leaving other registers unmodified
push rcx
push rbx
;initialization
mov rax, 0
mov rcx, userInputData
;start of loop
PARSEINT_LOOP_1:
xor rbx, rbx
mov bl, [rcx]
cmp rbx, 48
jl EXIT_PARSEINT_LOOP_1
cmp rbx, 57
jg EXIT_PARSEINT_LOOP_1
push rbx
mov rbx, 10
imul rbx
pop rbx
sub rbx, 48
add al, bl
inc rcx
jmp PARSEINT_LOOP_1
EXIT_PARSEINT_LOOP_1:
; restoring original values to the registers
pop rbx
pop rcx
ret

_newLine:
mov rax, 1
mov rdi, 1
mov rdx, 1
mov rsi, newLine
syscall
ret

section .text
global _start

_start:
	mov rax, 3
	;VAR a
	mov rcx, variables ; pointer to the variables
	mov [rcx+0], rax
	mov rax, 4
	push rax
	mov rax, 5
	pop rbx
	add rax, rbx
	;VAR b
	mov rcx, variables ; pointer to the variables
	mov [rcx+8], rax
	mov rcx, variables ; pointer to the variables
	mov rax, [rcx+0]
	push rax
	mov rcx, variables ; pointer to the variables
	mov rax, [rcx+8]
	pop rbx
	cmp rax, rbx
	sete al
	test al, al
	jz L01
	mov rcx, printText;
	mov bl, 'a'
	mov [rcx + 0], bl
	mov bl, ' '
	mov [rcx + 1], bl
	mov bl, 'i'
	mov [rcx + 2], bl
	mov bl, 's'
	mov [rcx + 3], bl
	mov bl, ' '
	mov [rcx + 4], bl
	mov bl, 'e'
	mov [rcx + 5], bl
	mov bl, 'q'
	mov [rcx + 6], bl
	mov bl, 'u'
	mov [rcx + 7], bl
	mov bl, 'a'
	mov [rcx + 8], bl
	mov bl, 'l'
	mov [rcx + 9], bl
	mov bl, ' '
	mov [rcx + 10], bl
	mov bl, 't'
	mov [rcx + 11], bl
	mov bl, 'o'
	mov [rcx + 12], bl
	mov bl, ' '
	mov [rcx + 13], bl
	mov bl, 'b'
	mov [rcx + 14], bl
	mov rdx, 15
	call _printText
	call _newLine
	jmp L00
	L01	:
	mov rcx, printText;
	mov bl, 'a'
	mov [rcx + 0], bl
	mov bl, ' '
	mov [rcx + 1], bl
	mov bl, 'i'
	mov [rcx + 2], bl
	mov bl, 's'
	mov [rcx + 3], bl
	mov bl, ' '
	mov [rcx + 4], bl
	mov bl, 'n'
	mov [rcx + 5], bl
	mov bl, 'o'
	mov [rcx + 6], bl
	mov bl, 't'
	mov [rcx + 7], bl
	mov bl, ' '
	mov [rcx + 8], bl
	mov bl, 'e'
	mov [rcx + 9], bl
	mov bl, 'q'
	mov [rcx + 10], bl
	mov bl, 'u'
	mov [rcx + 11], bl
	mov bl, 'a'
	mov [rcx + 12], bl
	mov bl, 'l'
	mov [rcx + 13], bl
	mov bl, ' '
	mov [rcx + 14], bl
	mov bl, 't'
	mov [rcx + 15], bl
	mov bl, 'o'
	mov [rcx + 16], bl
	mov bl, ' '
	mov [rcx + 17], bl
	mov bl, 'b'
	mov [rcx + 18], bl
	mov rdx, 19
	call _printText
	call _newLine
	L00	:
	mov rax, 60
	mov rdi, 0
	syscall
