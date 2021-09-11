#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char headerVars[1000];
char* header_declaration = "\n\
section .bss\n\
integer_buffer resb 100\n\
\n\
section .data\n\
userInputData times 8 db 0\n\
newLine db 10\n\
variables times 27 dq 0\n\
printText times 200 db 0\n\
\n\
section .text\n\
global _start\n\
\n\
_printRAX:\n\
; leaving other registers unmodified\n\
push rbx\n\
push rcx\n\
push rdi\n\
\n\
mov rcx, integer_buffer ; digit space\n\
mov rdi, 0 ; calculate offset\n\
\n\
_printRAXLoop1:\n\
mov rdx, 0 ; do this before division, said the gods\n\
mov rbx, 10\n\
div rbx ; divide by 10, for the remainder of course\n\
push rax\n\
add rdx, 48 ; add 48 to remainder, ascii conversion\n\
mov [rcx], dl ; store 8 bit value in the buffer\n\
inc rcx ; point to next address\n\
inc rdi ; increment offset\n\
pop rax\n\
\n\
cmp rax, 0\n\
jne _printRAXLoop1\n\
\n\
_printRAXLoop2:\n\
mov rcx, integer_buffer\n\
add rcx, rdi\n\
\n\
push rdi\n\
\n\
mov rax, 1\n\
mov rdi, 1\n\
mov rsi, rcx\n\
mov rdx, 1\n\
syscall\n\
\n\
pop rdi\n\
\n\
dec rdi\n\
\n\
cmp rdi, 0\n\
jge _printRAXLoop2\n\
\n\
pop rdi\n\
pop rcx\n\
pop rbx\n\
\n\
ret\n\
\n\
_printText:\n\
mov rax, 1\n\
mov rdi, 1\n\
mov rsi, printText\n\
syscall\n\
ret\n\
\n\
_getInputInteger:\n\
call _getInput\n\
call _parseInt\n\
ret\n\
\n\
_getInput:\n\
mov rax, 0\n\
mov rdi, 0\n\
mov rsi, userInputData\n\
mov rdx, 8\n\
syscall\n\
ret\n\
\n\
_parseInt:\n\
; leaving other registers unmodified\n\
push rcx\n\
push rbx\n\
;initialization\n\
mov rax, 0\n\
mov rcx, userInputData\n\
;start of loop\n\
PARSEINT_LOOP_1:\n\
xor rbx, rbx\n\
mov bl, [rcx]\n\
cmp rbx, 48\n\
jl EXIT_PARSEINT_LOOP_1\n\
cmp rbx, 57\n\
jg EXIT_PARSEINT_LOOP_1\n\
push rbx\n\
mov rbx, 10\n\
imul rbx\n\
pop rbx\n\
sub rbx, 48\n\
add al, bl\n\
inc rcx\n\
jmp PARSEINT_LOOP_1\n\
EXIT_PARSEINT_LOOP_1:\n\
; restoring original values to the registers\n\
pop rbx\n\
pop rcx\n\
ret\n\
\n\
_newLine:\n\
mov rax, 1\n\
mov rdi, 1\n\
mov rdx, 1\n\
mov rsi, newLine\n\
syscall\n\
ret\n\
\n\
_start:\n";



char *userDetails="\n\
; Author: Meetesh Kalpesh Mehta\n\
; Compiler Name: XOPE\n\
; year: 2020\n\
";

char *getHeaderDeclaration(char *VERSION, char *CHANGES, char *COMMENT) {
  sprintf(headerVars,"%s; version: %s \n; changes:%s\n; comment: %s\n",userDetails, VERSION, CHANGES, COMMENT);
  return (char *)headerVars;
}
