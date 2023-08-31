#ifndef KERNEL_H
#define KERNEL_H
#define MEMORY_START 0x1000
#define STACK_BASE 0x9000

int _start();

void MEMORY_COPY(char *src, char *dest, unsigned int length);
void MEMORY_SET(char *src, char value, unsigned int length);
void GET_GDTR(char *destAdress);

#endif