#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
#include "../headers/UTILS.h"
#include "../headers/GDT.h"

/*/BETTER IDEA


0x0 -> 0x799 IDT 8bytes per register, 256 registers

0x800 -> 0x999 GDT 8 bytes per register, 3 registers, one null and one for code and one for data, put GTDR right after the end

0x1000 to 0x2000 -> video buffer for text manipulation

0x2000 -> start of kernel

*/

int _start()
{

    // Careful because we might need to load more sectors from the disk
    // remember to load more sectors from bootloader and write more sectors on the burn of the iso

    // NEW GDT Init
    INIT_TABLES();
    // Why the fuck is the kernel also loaded in this adress?, dont matter but why?
    PRINT_MEMORY_DUMP(GET_GTD_BASE_ADRESS());

    while (1)
    {
    }
    return 0;
}

// Copies the memory from src to dest, all the way to length
void MEMORY_COPY(char *src, char *dest, uint length)
{
    for (int i = 0; i < length; i++)
    {

        dest[i] = src[i];
    }
}

// Sets the memory to value starting from src until the length
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

// Inits the GDT and IDT to the respective agreed memory adresses
void INIT_TABLES()
{
    // Initialization of the GDT
    struct GDT GLOBAL_DESCRITOR_TABLE;
    struct GDTR GLOBAL_DESCRITOR_TABLE_REGISTER;
    INIT_GDTR(&GLOBAL_DESCRITOR_TABLE_REGISTER);
    INIT_GDT(&GLOBAL_DESCRITOR_TABLE);
    MEMORY_COPY(&GLOBAL_DESCRITOR_TABLE, GTD_BASE_ADRESS, sizeof(struct GDT));
    MEMORY_COPY(&GLOBAL_DESCRITOR_TABLE_REGISTER, GTD_BASE_ADRESS + sizeof(struct GDT), sizeof(struct GDTR));
    SET_GDTR(0x800 + sizeof(struct GDT));

    // Initialization of the GDT
};
