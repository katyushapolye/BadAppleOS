#ifndef UTILS_H
#define UTILS_H

#define uint unsigned int
#define bool unsigned short int
#define TRUE 1
#define FALSE 0

#define NULL ((void *)0)

void hexToStr(int hex, char *dest);

void hexToStrRaw(int hex, char *dest);

void byteToHexStr(char byte, char *dest);

#endif