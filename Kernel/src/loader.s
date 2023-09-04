global loader                   ; the entry symbol for ELF
extern _start

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -(MAGIC_NUMBER + FLAGS) ; calculate the checksum

section .text                   ; start of the text (code) section
align 4                         ; the code must be 4 bytes aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

loader:                         ; the loader label (defined as the entry point in the linker script)
    mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register eax

KERNEL_STACK_SIZE equ 4096 ;;basic stack

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE ;;setting the stack hight

section .text
mov esp, kernel_stack + KERNEL_STACK_SIZE

.loop:
    jmp _start


