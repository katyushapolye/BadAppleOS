
#include "../headers/VGA_DRIVER.h"
#include "../headers/UTILS.h"
#include "../headers/IO.h"

// Prints a memory dump containing 16 bytes per line, not very efficient.
void PRINT_MEMORY_DUMP(char *adress)
{
    char *buffer = "00";

    for (int i = 0; i < 25; i++)
    {

        printHexToPosition(adress, 0, i);
        for (int j = 12; j < 60; j += 3)
        {

            byteToHexStr((*adress), buffer);
            printStringToPosition(buffer, j, i);
            printStringToPosition("  ", j + 2, i);
            (adress++);
        }

        // 0xffffffff - aa bb cc dd ee ff gg hh ii jj kk
    }
}

void disableCursor()
{
    // some witchcraft logic here because of old VGA hardware
    outByte(0xa, 0x3d4);  // sends the index of the register we want to write throught the data register
    outByte(0x10, 0x3d5); // writes to the register indexed by the previous instruction
    return;
}

// Just basic thing to get us running to the bare minimum
void CLEAR_GPU_VIDEO_MEMORY()
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

void printCharToPosition(char c, int x, int y)
{

    char *position = VIDEO_TEXT_MEMORY_START + ((2 * TEXT_SCREEN_WIDTH * y) + (2 * x));

    *(position + 1) = BLACK_BG;
    *position = c;
}

void printHexToPosition(int hex, int x, int y)
{
    char *str = "";
    hexToStr(hex, str);

    printStringToPosition(str, x, y);
}

// Prints a null terminated string to the designated position in the screen
void printStringToPosition(char *c, int x, int y)
{

    int k, j = 0;
    k = x;
    j = y;

    while (*c != '\0')
    {
        if (k >= 80)
        {
            k = 0;
            j++;
        }
        printCharToPosition(*c, k, j);
        k++;

        c++;
    }
    /*
    for (int i = 0; i < size; i++)
    {

        if (k >= 80)
        {
             k = 0;
            j++;
        }
        printCharToPosition(c[i], k, j);
        k++;
    }
    */
}

// Careful
void SWAP_BUFFER(char buffer[25][80])
{

    char *VIDEOMEM = VIDEO_TEXT_MEMORY_START;

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            (*VIDEOMEM) = buffer[i][j];
            *(VIDEOMEM + 1) = 0x0f;
            VIDEOMEM += 2;
        }
    }

    printHexToPosition(buffer[0], 32, 1); // Printing hex values for the first row
}
