
#include "../headers/VGA_DRIVER.h"

// Barebones good for nothing implementation
void PRINT_STR(char *string, int size)
{

    char *BUFFER = (char *)VIDEO_TEXT_MEMORY_START;
    int c = 0;
    for (int i = 0; i < 2 * size; i += 2)
    {
        BUFFER[i] = string[c];
        c++;
        BUFFER[i + 1] = BLACK_BG;
    }
}

// Just basic thing to get us running to the bare minimum
int CLEAR_VIDEO_MEMORY()
{

    int i = 0;
    char *buffer = (char *)VIDEO_TEXT_MEMORY_START;
    while (i < 4000)
    {
        *buffer = 0;
        buffer++;
        i++;
    }

    return;
}
