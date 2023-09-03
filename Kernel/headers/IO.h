#ifndef IO_H
#define IO_H

// Sends the byte "byte" to the designated IO port
void OUT_BYTE(char byte, short unsigned int port);

// Returns the byte read from the IO port
char IN_BYTE(short unsigned int port);

// Sends the word to the designated IO port, granting it can communicate using words
void OUT_WORD(unsigned short int word, short unsigned int port);

// Returns the word read from the IO port, assuming it can send words
unsigned short int IN_WORD(unsigned short int port);

void IO_WAIT();
#endif