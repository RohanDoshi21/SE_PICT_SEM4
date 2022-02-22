section .data
str1: db "No of positive numbers are: ", 0x9
len1: equ $- str1
str2: db 0xA

block dq 0x0123456701234567, 0xF123456701234567, 0xF123456701234567, 0xF123456701234567
count db 4

section .bss
result: resb 200

section .text
global _start

_start:

mov bl, 00
mov rsi, block

loop:
mov rax, qword[rsi]
bt rax, 63
jc label
inc bl

label:
add rsi, 08h          ; Add 8 to go to the next number
dec byte[count]
jnz loop

mov rax, 1
mov rdi, 1
mov rsi, str1
mov rdx, len1
syscall

add bl,0x30
mov [result], bl
mov rax, 1
mov rdi, 1
mov rsi, result
mov rdx, 16
syscall

mov rax, 1
mov rdi, 1
mov rsi, str2
mov rdx, 1
syscall

mov rax, 60
mov rdi, 00
syscall
