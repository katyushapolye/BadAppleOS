#include "../headers/KERNEL.h"

#include "../headers/VGA_DRIVER.h"
#include "../headers/UTILS.h"

int _start()
{

    // Careful because we might need to load more sectors from the disk
    // remember to load more sectors from bootloader and write more sectors on the burn of the iso

    char str[64];
    CLEAR_VIDEO_MEMORY();

    int GDT_BASE_ADRESS = 0;
    unsigned int gdt[1];
    GET_GDTR(gdt);
    GDT_BASE_ADRESS = gdt[0] >> (16); // little trick
    hexToStrRaw(GDT_BASE_ADRESS, str);
    PRINT_STR(str, 10);

    while (1)
    {
    }
    return 0;
}

void MEMORY_COPY(byte *src, byte *dest, uint length)
{
    for (int i = 0; i < length; i++)
    {

        dest[i] = src[i];
    }
}

// Sets the
void MEMORY_SET(byte *src, byte value, uint length)
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
void GET_GDTR(byte *destAdress)
{
    asm volatile(
        "sgdt %0"
        : "=m"(*destAdress)
        :
        : "memory"

    );
}