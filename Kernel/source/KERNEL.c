#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
#include "../headers/UTILS.h"

/* The memory  shall be set as

//0x000 ->
//0x200 -> 0x299 -> new GDT
//0x300 -> 0x499 -> IDT, can it fit?

// 0x500 -> start of the kernel code, undefined in size





// 0x7000 stack base adress


0x7d20-(0x7d20 + 42) -> old GDT -> need to change

should be free from here until 0xb8000, VGA memory, not mapped to physical



//BETTER IDEA


0x0 -> 0x799 IDT 8bytes per register, 256 registers

0x800 -> 0x999 GDT 8 bytes per register, 3 registers, one null and one for code and one for data, put GTDR right after the end

0x1000 to 0x2000 -> video buffer for text manipulation

0x2000 -> start of kernel

*/

int _start()
{

    // Careful because we might need to load more sectors from the disk
    // remember to load more sectors from bootloader and write more sectors on the burn of the iso

    int GDT_BASE_ADRESS = 0;
    unsigned int gdt[1];
    GET_GDTR(gdt);
    GDT_BASE_ADRESS = gdt[0] >> (16); // little trick
                                      // not a good ideia to pass these as a parameter

    // MEMORY_SET(0x0, 0xff, 0x90);
    // MEMORY_SET(0x90, 0xee, 0x90);

    // MEMORY_SET(0x120, 0x00, 0x90);

    // Why the fuck is the kernel also loaded in this adress?
    PRINT_MEMORY_DUMP(0x7d00);
    // PRINT_MEMORY_DUMP(0x500);
    MEMORY_SET(0x07e00, 0, 0xfffff); // clearing the whole memory
    PRINT_MEMORY_DUMP(0x07d00);

    while (1)
    {
    }
    return 0;
}

void MEMORY_COPY(char *src, char *dest, uint length)
{
    for (int i = 0; i < length; i++)
    {

        dest[i] = src[i];
    }
}

// Sets the
void MEMORY_SET(char *src, char value, uint length)
{
    int i = length;

    while (i)
    {
        *src = value;
        src++;
        i--;
    }
}

// Writes on destAdress the contents of the GDTR
void GET_GDTR(char *destAdress)
{
    asm volatile(
        "sgdt %0"
        : "=m"(*destAdress)
        :
        : "memory"

    );
}
