#include "../headers/GDT.h"
#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
// Inits the GDT struct
void INIT_GDT()
{

    struct GDT gdt;

    gdt.NULL_BASE = 0x0;
    gdt.NULL_LIMIT = 0x0;
    gdt.CODE_BASE_LOWER = 0xffff;
    gdt.CODE_BASE_LOWER = 0x0000;
    gdt.CODE_BASE_MIDDLE = 0x00;
    gdt.CODE_ACESS_BYTE = 0x9a;
    gdt.CODE_FLAG_LIMIT_TOP = 0xcf;
    gdt.CODE_BASE_TOP = 0x00;
    gdt.DATA_LIMIT_LOWER = 0xffff;
    gdt.DATA_BASE_LOWER = 0x0000;
    gdt.DATA_BASE_MIDDLE = 0x00;
    gdt.DATA_ACESS_BYTE = 0x92;
    gdt.DATA_FLAG_LIMIT_TOP = 0xcf;
    gdt.DATA_BASE_TOP = 0x00;
    MEMORY_COPY(&gdt, GDT_BASE_ADRESS, sizeof(struct GDT));
    struct GDTR gdtr;
    gdtr.base = GDT_BASE_ADRESS;
    gdtr.size = sizeof(struct GDT);
    MEMORY_COPY(&gdtr, GDT_BASE_ADRESS + sizeof(struct GDT), sizeof(struct GDTR));
    SET_GDTR(GDT_BASE_ADRESS + sizeof(struct GDT));
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

// Sets the GDTR based on the given adress
void SET_GDTR(char *srcAdress)
{
    asm volatile(
        "lgdt %0"
        : "=m"(*srcAdress)
        :
        : "memory"

    );
}
// Returns the base adress of the currently used GDT by the CPU
int GET_GDT_BASE_ADRESS()
{

    int adress = 0;
    unsigned int gdt[1];
    GET_GDTR(gdt);
    adress = gdt[0] >> (16); // little bit shift to get the adress
    return adress;
};

// Inits the GDTR based on the GDT struct
void INIT_GDTR(struct GDTR *gdtr)
{
    gdtr->size = sizeof(struct GDT); // 3 segs, each valued at 8 byes
    gdtr->base = 0x800;
}