#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
#include "../headers/UTILS.h"
#include "../headers/GDT.h"
#include "../headers/ISR.h"
#include "../headers/IDT.h"
#include "../headers/IO.h"

/*
I STILL HAVENT DECIDED A GOOD CONVENTION FOR NAMING FUNCTIONS AND DATA
IM BASICALLY WRITING IN ALL CAPS EVERYTHING I FIND IT VERY IMPORTANT OR ARCHAIC AND
IN NORMAL CAMELCASING LESS IMPORTANT THINGS
DOESNT WORK VERY WELL BU WHAT CAN I DO
I'LL PROBABLY NEVER FIX THIS

AT LEAST CONSTANTS AND DEFINES ARE ALWAYS IN ALL CAPS
IVE ALSO HAVE NOT MADE A DEFINITIONS HEADERS, SO IM JUST WRITING EVERYTIME
UNSIGNED SHORT INT INSTEAD OF SOMETHINK LIKE u_sint or some shit

I also need to check if the A21 line is active, I'm programming like it is but I think it is not since
if i write to a high adress it just fucking implodes my code


The memory layout shall be as follows
0x0 -> 0x799 IDT 8bytes per register, 256 registers

0x800 -> 0x999 GDT 8 bytes per register, 3 registers, one null and one for code and one for data, put GTDR right after the end

0x1000 to 0x2000 -> video buffer for text manipulation

0x2000 -> start of kernel code


*/

int _start()
{

    // Careful because we might need to load more sectors from the disk
    // remember to load more sectors from bootloader and write more sectors on the burn of the iso

    int *clock = 0x5000;
    (*clock) = 0;
    INIT_TABLES();
    ENABLE_INTERRUPTS();

    disableCursor();
    printStringToPosition("Timer: ", 0, 5);
    while (1)
    {
        printHexToPosition(*((int *)(0x5000)), 9, 5);
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

    INIT_GDT();
    INIT_IDT();

    char *buffer = "Adress of Loaded IDT: ";
    printStringToPosition(buffer, 0, 0);
    printHexToPosition(GET_IDT_BASE_ADRESS(), 24, 0);
    buffer = "Adress of Loaded GDT: ";

    printStringToPosition(buffer, 0, 1);
    printHexToPosition(GET_GDT_BASE_ADRESS(), 24, 1);
};

void ENABLE_INTERRUPTS()
{
    asm volatile("sti");
}

void DISABLE_INTERRUPTS()
{
    asm volatile("cli");
}
