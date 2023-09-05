#ifndef KERNEL_H
#define KERNEL_H
#define MEMORY_START 0x100000 // one mb
#define STACK_BASE 0x9000     // incorrect, I dont know where it is for now

int _start();

void MEMORY_COPY(char *src, char *dest, unsigned int length);
void MEMORY_SET(char *src, char value, unsigned int length);

#endif