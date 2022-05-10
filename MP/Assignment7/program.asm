%macro rwe 3
mov rax,%1
mov rdi,01
mov rsi,%2
mov rdx,%3
syscall
%endmacro

section .data
    block1 dq 1111111111111111h, 2222222222222222h, 3333333333333333h, 4444444444444444h
    msg1 db "Contents of Block1: ", 0xA
    len_msg1 equ $-msg1
    msg2 db "Contents of Block2: ", 0xA
    len_msg2 equ $-msg2

    msg3 db "Before ",0xA
    len_msg3 equ $-msg3 

    cnt db 4

section .bss
    block2 resq 4
    count resb 1
    result resq 1
    asciiarr resq 02

section .text
global _start

_start:
    mov rsi, block1
    mov rdi, block2
    mov cl, [cnt]

block_transfer:
    mov rax, [rsi]
    mov [rdi], rax

    add rsi, 08h
    add rdi, 08h

    dec cl
    jnz block_transfer

    mov cl, [cnt]

    rwe 01, msg3, len_msg3

    mov rsi, block1
    mov rax, qword[rsi]
    mov qword[result], rax
    call hextoascii

    mov rax, 60
    mov rdi, 0
    syscall

    
hextoascii:
          mov rsi, asciiarr
          mov byte[count], 16
          mov al,byte[result]	;hex to ascii conversion logic from here
down:     rol al,04h
          mov bl,al
          and bl,0fh
          cmp bl,09h
          jbe next
          add bl,07h
	
next:      add bl,30h
           mov [rsi],bl
           inc rsi
           dec byte[count]
           jnz down
           rwe 01,asciiarr,02h
           ret

    


