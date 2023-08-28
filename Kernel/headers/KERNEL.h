#ifndef KERNEL_H
#define KERNEL_H
#define MEMORY_START 0x1000
#define STACK_BASE 0x9000

#define byte char
#define uint unsigned int
#define bool unsigned short int
#define TRUE 1
#define FALSE 0

int _start();

void MEMORY_COPY(byte *src, byte *dest, uint length);
void MEMORY_SET(byte *src, byte value, uint length);
void GET_GDTR(byte *destAdress);

#endif