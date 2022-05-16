%macro print 2
    mov rax, 1
    mov rdi, 1
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

%macro input 2
    mov rax, 0
    mov rdi, 0
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

section .data
    msg1: db "Enter String: ", 0xA
    len1: equ $-msg1
    msg2: db "The length of the string is ", 0xA
    len2: equ $-msg2
    count: db 0

section .bss
    string: resb 20
    result: resb 20
    asciiarr resb 02
    strlen: resb 01

section .text
    global _start

_start:
    print msg1, len1
    input string, 20

    ;length of string is present in rax already
    ;dec rax
    ;mov [strlen], rax
    ;call hextoascii

    mov rsi, string
    mov byte[count], 00
loop:
    mov al, [rsi]
    cmp al, 10
    jz down1

    inc byte[count],
    inc rsi
    jmp loop

down1:
    mov al, byte[count]
    mov byte[strlen], al
    print msg2, len2
    call hextoascii

    mov rax,60
    mov rdi,00
    syscall

hextoascii:
    mov rsi,asciiarr
    mov byte[count],02h
    mov al,byte[strlen]
down:    
    rol al,04h
    mov bl,al
    and bl,0fh
    cmp bl,09h
    jbe next
    add bl,07h
	
next:      
    add bl,30h
    mov [rsi],bl
    inc rsi
    dec byte[count]
    jnz down
    print asciiarr,02h
    ret
