#include "../headers/GDT.h"

void INIT_GDT(struct GDT *gdt)
{

    char *str = "Hllo";
    gdt->NULL_BASE = 0x0;
    gdt->NULL_LIMIT = 0x0;

    gdt->CODE_BASE_LOWER = 0xffff;
    gdt->CODE_BASE_LOWER = 0x0000;
    gdt->CODE_BASE_MIDDLE = 0x00;
    gdt->CODE_ACESS_BYTE = 0x9a;
    gdt->CODE_FLAG_LIMIT_TOP = 0xcf;
    gdt->CODE_BASE_TOP = 0x00;

    gdt->DATA_LIMIT_LOWER = 0xffff;
    gdt->DATA_BASE_LOWER = 0x0000;
    gdt->DATA_BASE_MIDDLE = 0x00;
    gdt->DATA_ACESS_BYTE = 0x92;
    gdt->DATA_FLAG_LIMIT_TOP = 0xcf;
    gdt->DATA_BASE_TOP = 0x00;
}