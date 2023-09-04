#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
#include "../headers/UTILS.h"
#include "../headers/GDT.h"
#include "../headers/ISR.h"
#include "../headers/IDT.h"
#include "../headers/IO.h"
#include "../headers/frames.h"
#include "../headers/TIMER.h"

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
if i write to a high adress it just fucking implodes my code <- SOLVED


The memory layout shall be as follows
0x0 -> 0x799 IDT 8bytes per register, 256 registers

0x800 -> 0x820 GDT 8 bytes per register, 3 registers, one null and one for code and one for data, put GTDR right after the end

0x820 -> 0x840 -> system time information

0x1000 to 0x2000 -> video buffer for text manipulation <- I THINK I can rewrite all of the GRUB area

0xb8000 - 0xbc000-> Text GPU Buffer

0xA000 -> somewhere is the GPU buffer in Video mode

0x100000 -> after the first megabyte, start of kernel


*/

int _start()
{

    INIT_TABLES();
    ENABLE_INTERRUPTS();

    CLEAR_GPU_VIDEO_MEMORY();

    disableCursor();

    int i = 0;
    while (1)
    {
        if (GET_SYSTEM_TIME() > 333)
        {
            SWAP_BUFFER(frames[i]);
            RESET_SYSTEM_TIME();
            i++;
        }
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

void INIT_TIME_DATA()
{

    struct TIMERDATA tData;

    tData.IS_HALTED = 0x0000000000000000;
    tData.PADDING = 0x1111111111111111;
    tData.SYS_TIME = 0x0;
    tData.TARGET_TIME = 0x0;
    MEMORY_COPY(&tData, TIME_DATA_ADRESS, sizeof(tData));
}
