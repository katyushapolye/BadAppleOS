#include "../headers/IO.h"

// Reads a byte from the given port and returns it
char IN_BYTE(unsigned short int port)
{
    char result;

    __asm__("in %%dx,%%al" : "=a"(result) : "d"(port));
}

// Sends the byte to the designated port
void OUT_BYTE(char byte, unsigned short int port)
{
    char result;

    __asm__("out %%al, %%dx" : : "a"(byte), "d"(port));
}

// Waits for a short time, basically useless in modern systems but who knows...
void IO_WAIT()
{
    // writes to a (probably) useless and dead port to wait
    OUT_BYTE(0, 0x80); // port 0x80 was used by the bios during boot for something about the POST process
                       // according to LINUX, it is a useless port, so...
}
