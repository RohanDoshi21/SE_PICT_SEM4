;ALP to print "Helloworld"
section .data 
str: db "Hello "
len: equ $-str
str1: db "Welcome to PICT" ,0xA
len1: equ $-str1     
str2: db "Enter your Name: "
len2: equ $-str2

section .bss
name: resb 20


section .text 
global _start
_start:
	mov rax, 1                   ; 64 bit system call to print 
	mov rdi,1
	mov rsi, str2
	mov rdx, len2
	syscall
	mov rax, 0					; 64 bit system call to read
	mov rdx, 0
	mov rsi, name
	mov rdx, 20
	syscall
	mov rax, 1                   ; 64 bit system call to print 
	mov rdi,1
	mov rsi, str
	mov rdx, len
	syscall
	mov rax, 1                   ; 64 bit system call to print 
	mov rdi,1
	mov rsi, name
	mov rdx, 20
	syscall
	mov rax, 1                   ; 64 bit system call to print 
	mov rdi,1
	mov rsi, str1
	mov rdx, len1
	syscall
	mov rax , 60              ; 64 bit system call to exit
	mov rdi, 00
	syscall
