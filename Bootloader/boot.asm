[org 0x7c00] 
;0x7f00 is the end of the bootsector in memory
mov bx,0x1000 ;where to put it, from es*16 + bx(es:bx), given tthat es is zero default, it starts at bx
mov dh,32 ;sectors to read from cl (2)
mov dl,[BOOT_DRIVE] ;disk
call READ_DISK




cli ;clear all the IVT
lgdt [GDT_DESCRIPTOR]
mov bx,loadedGDT
mov cx,25
call print

mov eax , cr0 ; To make the switch to protected mode , we set
or eax , 0x1 ; the first bit of CR0 , a control register
mov cr0 , eax ; Update the control register


jmp CODE_SEG:PROTECTED_MODE

;PROTECTED_MODE:
;mov ebx,pm_string
;call PRINT_STRING
;jmp $


%include "functions.asm"
%include "data.asm"
%include "VGA_INTERFACE.asm"
%include "GDT.asm"

[bits 32]

PROTECTED_MODE:

mov ax , DATA_SEG ; repassing all of our seg registers to point to ou data seg on the gdt
mov ds , ax 
mov ss , ax 
mov es , ax
mov fs , ax
mov gs , ax
mov ebp , 0x9000 ; just trowy the stack anywhere high
mov esp , ebp 


mov ebx, pm_string
call PRINT_STRING
call CLEAR_VIDEO_MEMORY
mov eax,0x1000
jmp eax ;hardcoded entry point were we loaded our kernel
;we MIGHT use the C code to reposition the GDT to a better place in memory




times 510-($-$$) db 0 ;PADDING 
dw 0xaa55