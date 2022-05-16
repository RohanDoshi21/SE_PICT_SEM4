%macro print 2
    mov rax,01
    mov rdi,01
    mov rsi,%1
    mov rdx,%2
    syscall
%endmacro

section .data
    arr1 db 11h,22h,33h,44h,55h
    space db ' '
    newline db 10
    msg1: db 'Before overlapped :',0xa
    len1: equ $-msg1
    msg2: db 'After overlapped :',0xa
    len2: equ $-msg2

section .bss
    address resb 20
    data resb 5
    dig_count resb 2
    count resb 2
    arr2 resb 10

section .text
    global _start

_start:
    mov esi,arr1
    mov edi,arr2
    xor rcx,rcx
    mov cx,05
    cld

    rep movsb

    print msg1,len1
    mov byte[count],05
    mov rsi,arr1

up1: 
    mov rbx ,rsi
    push rsi
    call print_address
    print space,01
    pop rsi

    mov dl, [rsi]
    push rsi
    call print_data
    print newline,01
    pop rsi
    inc rsi
    dec byte[count]
    jnz up1

    print msg2,len2
    mov byte[count],05
    mov rsi,arr2

up3: 
    mov rbx ,rsi
    push rsi
    call print_address
    print space,01
    pop rsi

    mov dl,[rsi]
    push rsi
    call print_data
    print newline,01
    pop rsi
    inc rsi
    dec byte[count]
    jnz up3

exit:
    mov rax,60
    mov rdi,00
    syscall


print_address:
    mov byte[dig_count], 16
    mov rsi,address
    up: rol rbx,04
    mov al,bl
    and al,0Fh
    cmp al,09
    jbe l1
    add al,07h
    l1:add al,30h
    mov [rsi], al
    ;variable for printing
    inc rsi
    dec byte[dig_count]
    jnz up
    mov rax,01
    mov rdi,01
    mov rsi,address
    mov rdx,16
    syscall
ret


print_data:
    mov byte[dig_count],02
    mov rsi,data
    up2: rol dl,04
    mov al,dl
    and al,0Fh
    cmp al,09
    jbe l2
    add al,07h
    l2:add al,30h
    mov [rsi], al
    inc rsi
    dec byte[dig_count]
    jnz up2
    mov rax,01
    mov rdi,01
    mov rsi,data
    mov rdx,02
    syscall
ret
