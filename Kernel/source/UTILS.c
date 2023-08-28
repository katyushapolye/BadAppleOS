#include "../headers/UTILS.h"

void hexToStr(int hex, char *dest)
{
    // using some barrel shift and masks
    int mask = 0xf; // lowest 4 bits are 1111
    //
    int c = 2;
    dest[0] = '0';
    dest[1] = 'x';
    for (int i = sizeof(int) * 2 - 1; i >= 0; i--)
    {
        int lowBits = (hex >> (i * 4)) & mask; // extracts the last 4 bits of the original hex, based on the amount of shift with the index, note that
                                               // this converts from the end to the begging

        // optional, ignore left zeroes, need for a check if hit another since two
        if (lowBits < 10)
        {

            dest[c] = lowBits + '0';
        }

        if (lowBits >= 10 && lowBits < 16)
        {

            dest[c] = (lowBits - 10) + 'a';
        }
        c++;
    }
}

void hexToStrRaw(int hex, char *dest)
{
    // using some barrel shift and masks
    int mask = 0xf; // lowest 4 bits are 1111
    //
    int c = 0;
    int trail = 0; // for ignore to the left zeros
    for (int i = sizeof(int) * 2 - 1; i >= 0; i--)
    {
        int lowBits = (hex >> (i * 4)) & mask; // extracts the last 4 bits of the original hex, based on the amount of shift with the index, note that
                                               // this converts from the end to the begging

        // optional, ignore left zeroes, need for a check if hit another since two

        if (lowBits == 0 && !trail)
        {
            continue;
        }
        if (lowBits < 10)
        {
            trail = 1;
            dest[c] = lowBits + '0';
        }

        if (lowBits >= 10 && lowBits < 16)
        {
            trail = 1;
            dest[c] = (lowBits - 10) + 'a';
        }
        c++;
    }
}
