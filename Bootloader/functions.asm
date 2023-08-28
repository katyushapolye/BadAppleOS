
;bx is the adress of the string
;cx is the size of the string
print:
    pusha
    mov ah,0x0e
    
    printLoop:

        mov dx,[bx]

        add bx,1
        add cx,-1

        mov al,dl
        int 0x10

        cmp cx,0
        jne printLoop

    popa
    ret


;read DH sectors after bootloader and throws them into es:bx
READ_DISK:
    push dx ;sectors to read 



    mov ah,0x02
    mov al, dh ;how many sectors to read
    mov ch,0x00 ;cylinder 0
    mov dh,0x00 ;head 0
    mov cl,0x02 ;start reading from sector 2, right after bootsect

    ;check carry flag for errors on HD
    int 0x13
    jc DISK_ERROR

    ;check numbers of sectors actually read
    pop dx
    cmp dh,al
    jne DISK_ERROR
    ret


DISK_ERROR:
    mov bx,error_string
    mov cx,31
    call print
    jmp $










