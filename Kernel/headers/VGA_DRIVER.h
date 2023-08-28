#ifndef VGA_DRIVER_H
#define VGA_DRIVER_H

#define VIDEO_TEXT_MEMORY_START 0xb8000
#define VIDEO_TEXT_MEMORY_END 0xbc0000

#define BLACK_BG 0x0f

int CLEAR_VIDEO_MEMORY();
void PRINT_STR(char *string, int size);

#endif