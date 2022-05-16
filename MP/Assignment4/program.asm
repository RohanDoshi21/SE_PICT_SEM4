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
    choice: db 00h
    menu: db "Menu 1.Add 2.Subtract 3.Multiply 4.Divide 5.Exit ,Enter your choice : ", 10
    len1: equ $-menu 

    n1: dq 0x06
    n2: dq 0x02

section .bss
    sum: resb 1
    diff: resb 1
    prod: resb 1
    quot: resb 1
    result: resb 1
    asciiarr: resb 02
    count: resb 1

section .text
    global _start

_start:

main:
    print menu, len1
    input choice, 10

    sub byte[choice], 30h

    cmp byte[choice], 01
    jz addition

    cmp byte[choice], 02
    jz subtraction

    cmp byte[choice], 03
    jz multiplication

    cmp byte[choice], 04
    jz division

    cmp byte[choice], 05
    jz exit

addition: 
    mov rax, [n1]
    mov rbx, [n2]
    add rax, rbx
    mov [result], rax
    call hextoascii
    jmp main

subtraction: 
    mov rax, [n1]
    mov rbx, [n2]
    sub rax, rbx
    mov [result], rax
    call hextoascii
    jmp main

division: 
    mov rax, [n1]
    mov rbx, [n2]
    div rbx
    mov [result], rax
    call hextoascii
    jmp main

multiplication:
    mov rax, [n1]
    mov rbx, [n2]
    mul rbx
    mov [result], rax
    call hextoascii
    jmp main

exit:
    mov rax, 60
    mov rdi, 0
    syscall


hextoascii:
    mov rsi,asciiarr
    mov byte[count],0x10
    mov rax, [result]
down:    
    rol rax,04h
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
    print asciiarr, 0x10
    ret
