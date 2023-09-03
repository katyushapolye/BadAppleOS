#include "../headers/IDT.h"
#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
#include "../headers/ISR.h"
#include "../headers/IO.h"

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
    //
    INIT_GATE(&IDT, 0, &DIV_BY_ZERO, TRAP_GATE_TYPE);

    // some retarded test
    INIT_GATE(&IDT, 32, &PIT_INTERRUPT, INTERRUPT_GATE_TYPE);
    INIT_GATE(&IDT, 33, &KERNEL_PANIC, INTERRUPT_GATE_TYPE);

    // Copies the struct to the begging of the agreed mem location
    MEMORY_COPY(&IDT, 0x0, 0x800);

    struct IDTR idtr;
    idtr.base = 0x0000;
    idtr.size = 8 * 256; //
    SET_IDTR(&idtr);

    // Lets try to make this shit work

    // REMAPPING THE FUCKING PIC BECAUSE OF IBM'S RETARDED IDEAS
    IO_WAIT();

    // Ill probably just do what was on the linux kernel
    // keep in mind 0x20 is the main pic control port and 0x21 is the main pic data port
    // in similar fashion, the 0xa0 is the slave pic control port and 0xa1 is the slave pic data port

    OUT_BYTE(0x11, PIC_MASTER_CONTROL_PORT); // send init sequence to main pic
    IO_WAIT();                               // If we want, we would just throw 2 of these because of paranoia
    OUT_BYTE(0x11, PIC_SLAVE_CONTROL_PORT);  // send init sequence to slave pic
    IO_WAIT();
    OUT_BYTE(0x20, PIC_MASTER_DATA_PORT); // say to the main pic where to start its IRQ's (32) cuz intel maps the exceptions from the
    IO_WAIT();                            // cpu from 0-31, so we start from the first empty one
    OUT_BYTE(0x28, PIC_SLAVE_DATA_PORT);  // same thing for slave pic, main pic has 8 int while the slave has...6 or 7, i dont remember
    IO_WAIT();
    OUT_BYTE(0x04, PIC_MASTER_DATA_PORT); // signals to main pic that he is the main
    IO_WAIT();
    OUT_BYTE(0x02, PIC_SLAVE_DATA_PORT); // signals to the slave pich that he is a slave

    IO_WAIT();
    OUT_BYTE(0x01, PIC_MASTER_DATA_PORT); // I dont know what the fuck this is
    IO_WAIT();
    OUT_BYTE(0x01, PIC_SLAVE_DATA_PORT); // its suposed to say that they are 8086 ints'

    // mask off all ints, (same as disabling them)
    // The mask has 8 bits, there are 8 ints
    // setting the corresponding bit to 1 masks the input
    // ILl just set the PIT interrput for now setting only the first byte to 0
    OUT_BYTE(0xfc, PIC_MASTER_DATA_PORT);
    IO_WAIT();
    OUT_BYTE(0xff, PIC_SLAVE_DATA_PORT);
    IO_WAIT();
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
