#ifndef VGA_DRIVER_H
#define VGA_DRIVER_H

#define TEXT_SCREEN_HEIGHT 25

#define TEXT_SCREEN_WIDTH 80

#define VIDEO_TEXT_MEMORY_START 0xb8000
#define VIDEO_TEXT_MEMORY_END 0xbc0000

#define BLACK_BG 0x0f

// Clears the whole video memory
void CLEAR_VIDEO_MEMORY();

// Prints a string to the top of the buffer until its size
void PRINT_STR(char *string, int size);

// Prints a memory dump form the starting adress until the end of the screen buffer
void PRINT_MEMORY_DUMP(char *startingAdress);

// Takes the 80X25 buffer given and swaps with the current video buffer
void SWAP_BUFFER(const char **buffer);

// Prints a char to the position given
void printCharToPosition(char c, int x, int y);

#endif