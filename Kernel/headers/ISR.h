#ifndef ISR_H
#define ISR_H
#include "IDT.h"

__attribute((interrupt)) void DIV_BY_ZERO(INTERRUPT_FRAME *context);

#endif