%macro print 2
    mov rax, 1
    mov rdi, 1
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

section .data
    title: db 0x0A,"----Assignment 6-----", 0x0A
    title_len: equ $-title

    reg_msg: db 0x0A,"***** REGISTER CONTENTS *****"
    reg_msg_len: equ $-reg_msg

    ;GDTR is 48-bit lower 16 bit is limit upper is base
    gdtr_msg: db 0x0A,"Contents of GDTR : "
    gdtr_msg_len: equ $-gdtr_msg

    ;LDTR is 16 bit
    ldtr_msg: db 0x0A,"Contents of LDTR : "
    ldtr_msg_len: equ $-ldtr_msg

    ;IDTR is 48-bit lower 16 bit is limit upper is base
    idtr_msg: db 0x0A,"Contents of IDTR : "
    idtr_msg_len: equ $-idtr_msg

    ;TR is 16 bit
    tr_msg: db 0x0A,"Contents of TR : "
    tr_msg_len: equ $-tr_msg

    ;MSW is lower 16 bit of CRO
    msw_msg: db 0x0A,"Contents of MSW : "
    msw_msg_len: equ $-msw_msg

    real_msg: db "---- In Real mode. ----"
    real_msg_len: equ $-real_msg

    prot_msg: db "---- In Protected Mode. ----"
    prot_msg_len: equ $-prot_msg

    cnt2: db 04H
    newline: db 0x0A


section .bss
    gdtr: resd 1 
    ldtr: resw 1
    idtr: resd 1 
    msw: resd 1
    tr: resw 1
    value :resb 4

section .text
    global _start

_start:
    print title,title_len

    smsw [msw]
    mov eax,dword[msw]
    bt eax,0
    jc next

    print real_msg, real_msg_len
    jmp EXIT

next:
	print prot_msg, prot_msg_len
	print reg_msg, reg_msg_len


	print gdtr_msg, gdtr_msg_len
	SGDT [gdtr]
	mov bx, word[gdtr+4]
	call HtoA
	mov bx, word[gdtr+2]
	call HtoA
	mov bx, word[gdtr]
	call HtoA


    print ldtr_msg, ldtr_msg_len
    SLDT [ldtr]
    mov bx, word[ldtr]
    call HtoA


    print idtr_msg, idtr_msg_len
    SIDT [idtr]
    mov bx, word[idtr+4]
    call HtoA
    mov bx, word[idtr+2]
    call HtoA
    mov bx, word[idtr]
    call HtoA


    print tr_msg, tr_msg_len
    mov bx, word[tr]
    call HtoA   


    print msw_msg, msw_msg_len
    mov bx, word[msw+2]
    call HtoA
    mov bx, word[msw]
    call HtoA
    print newline, 1


EXIT:
    mov rax, 60
    mov rdi, 0
    syscall


HtoA:
    mov rdi, value
    mov byte[cnt2], 4H
aup:
    rol bx, 04
    mov cl, bl
    and cl, 0FH
    cmp cl, 09H
    jbe ANEXT
    ADD cl, 07H
ANEXT: 
    add cl, 30H
    mov byte[rdi], cl
    INC rdi
    dec byte[cnt2]
    JNZ aup
    print value, 4
    ret
