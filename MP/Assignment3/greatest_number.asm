section .data
str1: db "The greatest number in array is : ", 0xA
len1: equ $- str1

block dq 0xF123456701234568, 0xF123456701234567, 0xF123456701234569, 0xF123456701234564

count db 04h
cnt: db 0h

greatest: dq 0x0000000000000000	;initialize the greatest number to be the smallest 64 bit hex number

section .bss
result: resb 0

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

mov rsi, block        ; set rsi to point to block

mainloop:
mov rax, qword[rsi]   ; get the block number into rax
CMP rax, qword[greatest]
JBE down
mov qword[greatest], rax

down:
add rsi, 08h          ; add 8 to get to next number
dec byte[count]
jnz mainloop

; Convert the hex number to display on screen

mov rax, qword[greatest]
mov byte[cnt], 0x10
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

print str1, len1
print result, 16


mov rax, 60
mov rdi, 00
syscall
