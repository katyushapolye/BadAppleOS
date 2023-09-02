CC = gcc
LD = ld
CFLAGS = -O0 -m32 -ffreestanding -fno-zero-initialized-in-bss -fno-pie
LDFLAGS = --nmagic -m elf_i386 -Ttext 0x2000 --oformat binary

SRC_DIR = Kernel/source
OBJ_DIR = Kernel/object
BIN_DIR = Kernel/bin

SRC_FILES = $(SRC_DIR)/KERNEL.c  $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(BIN_DIR)/kernel.bin

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/kernel.bin: $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/kernel.bin

# Add a new target to create the ISO image
iso: $(BIN_DIR)/kernel.bin
	dd if=/dev/zero of=iso/rawIso.img bs=1024 count=1440
	dd if=Bootloader/bin/Bootloader.bin of=iso/rawIso.img seek=0 count=1 conv=notrunc
	dd if=$(BIN_DIR)/kernel.bin of=iso/rawIso.img seek=1 count=32 conv=notrunc

# Add a new target to create the ISO file
iso-image: iso
	genisoimage -V 'MYOS' -input-charset iso8859-1 -o iso/myos.iso -b rawIso.img -hide rawIso.img iso/

# Add a target to run a virtual machine (e.g., QEMU)
run-vm: iso-image
	qemu-system-i386 -cdrom iso/myos.iso

# Include a target to perform all steps at once
build-and-run: clean run-vm

