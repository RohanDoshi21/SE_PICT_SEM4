section .data
msg1: db "Limit of GDT is: ", 0xA
msg2: db "Base address of GDT is ", 0xA
gdtadd: dq 00h

section .bss
gdt: resb 0

%macro print 2
mov rax, 1
mov rdi, 1
mov rsi, %1
mov rdx, %2
syscall
%endmacro

section .text
global _start

_start: 

SGDT [gdt]
mov bx, byte[gdtadd]

l1:
print bx, 5

mov bx, byte[gdtadd + 4]
l1: 
print bx, 5

mov bx, byte[gdtadd + 2]
l1: 
print bx, 5




mov rax, 60
mov rdi, 00
syscall

// Procedure to convert Hex to ASCII
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

ret