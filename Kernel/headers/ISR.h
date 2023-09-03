#ifndef ISR_H
#define ISR_H
#include "IDT.h"

__attribute((interrupt)) void DIV_BY_ZERO(INTERRUPT_FRAME *context);

__attribute((interrupt)) void KERNEL_PANIC(INTERRUPT_FRAME *context);

// PIC INTS (ISQ's)
__attribute((interrupt)) void PIT_INTERRUPT(INTERRUPT_FRAME *context);
__attribute((interrupt)) void KEYBOARD_INTERRUPT(INTERRUPT_FRAME *context);

#endif