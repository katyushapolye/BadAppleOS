#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
#include "../headers/ISR.h"
#include "../headers/IO.h"
// This shall contain all interrupt service routines that are not the default ones
// Its on the init idt function that these are assigned to their respective gates
void DIV_BY_ZERO(INTERRUPT_FRAME *context)
{
    CLEAR_GPU_VIDEO_MEMORY();
    printStringToPosition("DIVISION BY ZERO - SKIPPING INSTRUCTION", 0, 0);
    context->eip++;
}

// Last resort ISR for unrecoverable exception
void KERNEL_PANIC(INTERRUPT_FRAME *context)
{

    CLEAR_GPU_VIDEO_MEMORY();
    printStringToPosition("KERNEL PANIC - UNRECOVERABLE EXCEPTION", 0, 0);
    printStringToPosition("INTERRUPT FRAME DATA: ", 0, 1);
    printStringToPosition("EIP: ", 0, 2);
    printStringToPosition("CS: ", 0, 3);
    printStringToPosition("EFLAGS: ", 0, 4);
    printStringToPosition("SP: ", 0, 5);
    printStringToPosition("SS: ", 0, 6);

    printHexToPosition(context->eip, 11, 2);
    printHexToPosition(context->cs, 11, 3);
    printHexToPosition(context->eflags, 11, 4);
    // printHexToPosition(context->sp, 11, 5);
    // printHexToPosition(context->ss, 11, 6);
    __asm__("hlt");
    return; // never reached
};

// interrupt from the PIT, triggers at a certain interval
// every 55ms if the wiki is right
// Ill just slap some funcking retarded test to see if is working
void PIT_INTERRUPT(INTERRUPT_FRAME *contex)
{
    long int *clock = 0x5000;
    (*clock)++;
    // ack of end of the ISQ/ISR (EOI) to the PIC, only used for IRQ ints
    OUT_BYTE(0x20, PIC_MASTER_CONTROL_PORT); // if it is on the second pic, it is also 0x20
    return;
}

void KEYBOARD_INTERRUPT(INTERRUPT_FRAME *context)
{
    printStringToPosition("Keyboard Pressed - Interrupt Catched", 0, 3);
    OUT_BYTE(0x20, PIC_MASTER_CONTROL_PORT); // ack of int end
    return;
}
