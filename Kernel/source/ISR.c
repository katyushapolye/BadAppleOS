#include "../headers/KERNEL.h"
#include "../headers/VGA_DRIVER.h"
#include "../headers/ISR.h"

void DIV_BY_ZERO(INTERRUPT_FRAME *context)
{
    CLEAR_GPU_VIDEO_MEMORY();
    printStringToPosition("DIVISION BY ZERO - SKIPPING INSTRUCTION", 0, 0);
    context->eip++;
}
