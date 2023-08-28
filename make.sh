
sh ./clear.sh

nasm -f bin Bootloader/boot.asm -o Bootloader/bin/Bootloader.bin -I Bootloader/



for file in Kernel/source/*;do
    filename=$(basename $file) 
    gcc -O0 -m32 -ffreestanding -fno-pie -c Kernel/source/$filename -o  Kernel/object/${filename%.*}.o
done

#objcopy -O binary -j .text Kernel/object/* Kernel/bin/kernel.bin
ld  --nmagic -m elf_i386 -o Kernel/bin/kernel.bin -Ttext 0x7e00 Kernel/object/* --oformat binary #Ttext is where the code is put INTO THE DISK ECTOR,
#it uses this value to calculate funcion calls and offsets, since there is no dynamic alocation, only code

dd if=/dev/zero of=iso/rawIso.img bs=1024 count=1440
dd if=Bootloader/bin/Bootloader.bin of=iso/rawIso.img seek=0 count=1 conv=notrunc
dd if=Kernel/bin/kernel.bin of=iso/rawIso.img seek=1 count=16 conv=notrunc #careful for not loading all of kernel, write more if the kernal starts getting bigger,
#each sector is 512 bytes



genisoimage -V 'MYOS' -input-charset iso8859-1 -o iso/myos.iso -b rawIso.img -hide rawIso.img iso/



#hd -v iso/rawIso.img > isoDump.txt dump of iso image
#ndisasm -b 32 iso/rawIso.img > PCK.dis Dissassamble of the iso image
qemu-system-i386 -cdrom iso/myos.iso



