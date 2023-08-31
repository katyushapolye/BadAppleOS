#ifndef VGA_DRIVER_H
#define VGA_DRIVER_H

#define TEXT_SCREEN_HEIGHT 25

#define TEXT_SCREEN_WIDTH 80

#define VIDEO_TEXT_MEMORY_START 0xb8000
#define VIDEO_TEXT_MEMORY_END 0xbc0000

#define BLACK_BG 0x0f

// Clears the whole video memory, can throw exception if no buffer has been set
void CLEAR_GPU_VIDEO_MEMORY();

// Prints a memory dump form the starting adress until the end of the screen buffer
void PRINT_MEMORY_DUMP(char *startingAdress);

// Prints a char to the position given
void printCharToPosition(char c, int x, int y);

// Replaces the display buffer with the given buffer
void SWAP_BUFFER(char buffer[25][80]);

// Prints a null terminated string starting from the given coords, retakes to the side if overflows
void printStringToPosition(char *c, int x, int y);

// Prints a Hex to the given screen coords
void printHexToPosition(int hex, int x, int y);

#endif