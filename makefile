CC = gcc
LD = ld
AS = nasm
CFLAGS = -O0 -m32 -ffreestanding -fno-pie -mgeneral-regs-only
LDFLAGS = --nmagic -m elf_i386 -Ttext 0x2000 --oformat binary
ASFLAGS = -f elf

SRC_DIR = Kernel/source
OBJ_DIR = Kernel/object
BIN_DIR = Kernel/bin

# List your C source files explicitly, ensuring KERNEL.c is the first.
SRC_FILES_C = $(SRC_DIR)/KERNEL.c $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES_C = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES_C))
SRC_FILES_ASM = $(wildcard $(SRC_DIR)/*.asm)
OBJ_FILES_ASM = $(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(SRC_FILES_ASM))

all: $(BIN_DIR)/kernel.bin

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/kernel.bin: $(OBJ_FILES_C) $(OBJ_FILES_ASM)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -rf iso/*
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/kernel.bin

dump-obj:
	./dump.sh

# Add a new target to create the floppy img
iso: $(BIN_DIR)/kernel.bin
	dd if=/dev/zero of=iso/rawIso.img bs=20k count=144
	dd if=Bootloader/bin/Bootloader.bin of=iso/rawIso.img seek=0 count=1 conv=notrunc
	dd if=$(BIN_DIR)/kernel.bin of=iso/rawIso.img seek=1 bs=512 count=2048 conv=notrunc

# Add a new target to create the ISO file
iso-image: iso
	genisoimage -o iso/myos.iso -b rawIso.img iso/ 

# Add a target to run a virtual machine (e.g., QEMU)
run-vm: iso-image
	qemu-system-i386 -m 4096 -cdrom iso/myos.iso
# Include a target to perform all steps at once
build-and-run: clean dump-obj run-vm
