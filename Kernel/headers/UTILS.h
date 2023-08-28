#ifndef UTILS_H
#define UTILS_H

// Converts a hex number to a String containing the values, not truncated, always 10 in size
void hexToStr(int hex, char *dest);

// Convert a hex number to a string, now left zeroes and no prefix 0x
void hexToStrRaw(int hex, char *dest);

#endif