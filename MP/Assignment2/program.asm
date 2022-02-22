section .data

str1: db "Enter the string: ", 0xA
len1: equ $- str1

str2: db "The length of the String is: ",0xA
len2: equ $- str2

cnt: db 0

section .bss
name: resb 200
result: resb 200

section .text
global _start

_start:

mov rax, 1
mov rdi, 1
mov rsi, str1
mov rdx, len1
syscall

mov rax, 0
mov rdi, 0
mov rsi, name
mov rdx, 200
syscall

dec rax
mov byte[cnt], 16
mov rsi, result

l1:
rol rax, 4
mov bl, al
and bl, 0x0F
cmp bl, 0x09
jbe l2
add bl, 07h

l2:
add bl, 30h
mov [rsi], bl
inc rsi
dec byte[cnt]
jnz l1

mov rax, 1
mov rdi, 1
mov rsi, str2
mov rdx, len2
syscall

mov rax, 1
mov rdi, 1
mov rsi, result
mov rdx, 16
syscall

mov rax, 60
mov rdi, 00
syscall
