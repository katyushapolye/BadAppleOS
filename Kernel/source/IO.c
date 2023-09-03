#include "../headers/IO.h"

// Reads a byte from the given port and returns it
char inByte(unsigned short int port)
{
    char result;

    __asm__("in %%dx,%%al" : "=a"(result) : "d"(port));
}

// Sends the byte to the designated port
void outByte(char byte, unsigned short int port)
{
    char result;

    __asm__("out %%al, %%dx" : : "a"(byte), "d"(port));
}
