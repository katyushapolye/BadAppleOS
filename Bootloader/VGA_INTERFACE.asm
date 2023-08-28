[ bits 32]
; Define some constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
; prints a null - terminated string pointed to by EBX
PRINT_STRING :
    pusha
    mov edx,VIDEO_MEMORY
    PRINT_STRING_LOOP:

        mov al,[ebx]
        mov ah,WHITE_ON_BLACK
        cmp al,0    
        je PRINT_STRING_END
        mov [edx],ax
        add edx,2
        add ebx,1
        jmp PRINT_STRING_LOOP

    PRINT_STRING_END:
    popa
    ret



;eax is the mem start adress
;ebx is the lenght of the dump
PRINT_MEMORY_DUMP:
    ;push eax
    push edx
    push ecx

    mov esi, ebx ;for fuck sake, find a way to use the stack instead of this shit
    mov edx,VIDEO_MEMORY
    mov ecx,0

    PRINT_MEMORY_DUMP_LOOP:

        mov bh,WHITE_ON_BLACK
        mov bl,[eax+ecx]   
        mov [edx],bx 
        add edx,2
        add ecx,1
        cmp ecx,esi
        jne PRINT_MEMORY_DUMP_LOOP

    ;pop eax
    pop ecx
    pop edx
    ret


;clears
CLEAR_VIDEO_MEMORY:
    pusha
    mov ecx,0
    mov eax,0
    mov edx,VIDEO_MEMORY
    ;4000 bytes of zeros from VIDEO MEM
    CLEAR_VIDEO_MEM_LOOP:
        mov [edx],eax   
        add edx,1
        add ecx,1
        cmp ecx,4000
        jne CLEAR_VIDEO_MEM_LOOP
    popa
    ret
