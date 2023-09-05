rm Kernel/object/*

rm os.iso

nasm -f elf32 Kernel/src/loader.s -o Kernel/object/loader.o
#!/bin/bash
SOURCE_FILES=(
    KERNEL.c
    GDT.c
    IDT.c
    IO.c
    ISR.c
    UTILS.c
    VGA_DRIVER.c
    TIMER.c
)

for source_file in "${SOURCE_FILES[@]}"; do
    object_file="Kernel/object/${source_file%.c}.o"
    gcc -m32 -ffreestanding -fno-stack-protector -nostartfiles -nostdlib -mgeneral-regs-only -c \
        "Kernel/src/$source_file" -I Kernel/headers/ -o "$object_file"
done


ld -T linker.ld -melf_i386 Kernel/object/* -o iso/boot/kernel.elf


genisoimage -R \
            -b boot/grub/stage2_eltorito \
            -no-emul-boot \
            -boot-load-size 4 \
            -A os  \
            -input-charset utf8 \
            -boot-info-table \
            -o os.iso \
            iso

            

qemu-system-i386 -cdrom os.iso