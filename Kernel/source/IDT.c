#include "../headers/IDT.h"
#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
#include "../headers/ISR.h"

/*Initializes a Interrupt gate of type "type" to the IDT, given the routine adress and the index on the IDT
As the GDT only contains one segment for code, the segment descriptor always inits to it*
THe Type is 0x8e for interrupt gate and 0x8f for trap gate*/
// Inits for default exception handles, does not take care of PIC and Intel's conflicting interrupt codes
void INIT_IDT()
{

    // Settinh up intels exception handlers
    struct IDT_GATE IDT[256];

    for (int i = 0; i < 32; i++)
    {
        if (i == 8 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 17 || i == 21)
        {
            INIT_GATE(&IDT, i, &DEFAULT_EXCEPT_HANDLER_ERROR_CODE, TRAP_GATE_TYPE);
        }
        else
        {
            INIT_GATE(&IDT, i, &DEFAULT_EXCEPT_HANDLER, TRAP_GATE_TYPE);
        }
    }

    for (int i = 32; i < 256; i++)
    {
        INIT_GATE(&IDT, i, &DEFAULT_INTERRUPT, INTERRUPT_GATE_TYPE);
    }

    // Particular types of except/int

    INIT_GATE(&IDT, 0, &DIV_BY_ZERO, TRAP_GATE_TYPE);

    // Copies the struct to the begging of the agreed mem location
    MEMORY_COPY(&IDT, 0x0, 0x800);

    struct IDTR idtr;
    idtr.base = 0x0000;
    idtr.size = 8 * 256; //
    SET_IDTR(&idtr);
}

void INIT_GATE(struct IDT_GATE *IDTbaseAdress, int index, void *isr, short int type)
{

    struct IDT_GATE gate;
    gate.OFFSET_LOW = ((int)isr) & 0xffff;
    gate.OFFSET_HIGH = (((int)isr) >> (16)) & 0xfff;
    gate.SEG_SELECTOR = 0x08; // the offset on the gdt containg code seg -> after the null desc, it is the first
    gate.ZERO = 0;
    gate.TYPE = type;
    IDTbaseAdress[index] = gate;

    return;
}

void DEFAULT_EXCEPT_HANDLER(INTERRUPT_FRAME *context)
{
    printStringToPosition("EXCEPTION TRIGGERED - NON ERROR CODE", 0, 0);
}

void DEFAULT_EXCEPT_HANDLER_ERROR_CODE(INTERRUPT_FRAME *context, unsigned int errorCode)
{
    printStringToPosition("EXCEPTION TRIGGERED - ERROR CODE:", 0, 0);
    printHexToPosition(errorCode, 35, 0);
}

void DEFAULT_INTERRUPT(INTERRUPT_FRAME *context)
{
    printStringToPosition("INTERRUPT TRIGGERED", 0, 0);
}

void SET_IDTR(char *srcAdress)
{
    asm volatile(
        "lidt %0"
        : "=m"(*srcAdress)
        :
        : "memory"

    );
}
void GET_IDTR(char *destAdress)
{
    asm volatile(
        "sidt %0"
        : "=m"(*destAdress)
        :
        : "memory"

    );
}

int GET_IDT_BASE_ADRESS()
{

    int IDT_BASE_ADRESS = 0;
    unsigned int idt[1];
    GET_IDTR(idt);
    IDT_BASE_ADRESS = idt[0] >> (16); // little bit shift to get the adress
    return IDT_BASE_ADRESS;
};
