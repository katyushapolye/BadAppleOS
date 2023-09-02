
#define GDT_H
#define GTD_BASE_ADRESS 0x800

struct GDTR
{
    unsigned short int size; // 16 bit int
    unsigned long int base;  // 32 bit
} __attribute__((packed));   // doesnt align memory with padding

struct GDT // Fixed on two segs, overlapping, the barely functional barebones implementation  by intel
{
    // NULL SEGMENT DESCRIPTOR
    unsigned int NULL_LIMIT; // = 0x0; // Sum of 8 bytes per segs
    unsigned int NULL_BASE;  // = 0x0;
    /*================START CODE SEG DESCRITPR=================*/

    unsigned short int CODE_LIMIT_LOWER; // 0xffff;
    unsigned short int CODE_BASE_LOWER;  // 0x0000;

    unsigned char CODE_BASE_MIDDLE; // 0x00;

    unsigned char CODE_ACESS_BYTE; // 0x9a; // to see
    // bunch of flags to define acess level
    // 1001 1010b
    // first bit is if it is present in memory 1
    // second bit and third bit is permission level 0,1,2,or 3, 0 for kernel so 00
    // forth bit is always 1
    // fitth bit is if the segment is executable 1
    // sixth bit is if the segment is stack, growing down 0
    // seventh bit is if the segment is readble 1
    // eight bit is if the segment is being acessed by the cpu, Initially set to 0

    unsigned char CODE_FLAG_LIMIT_TOP; // 0xcf; // split half/half flag half limit
    // flags =  1 1 0 0 // Limit = 0xf = 1 1 1 1-> 11001111b = 0xcf
    // first bit granularity
    // second bit is if 16bit or 32 bit

    unsigned char CODE_BASE_TOP; // 0x00;
    /*================START DATA SEG DESCRITPR=================*/

    unsigned short int DATA_LIMIT_LOWER; // 0xffff;
    unsigned short int DATA_BASE_LOWER;  // 0x0000;

    unsigned char DATA_BASE_MIDDLE; // 0x00;

    unsigned char DATA_ACESS_BYTE; // 0x92; // to see
    // bunch of flags to define acess level
    // 1001 0010b
    // first bit is if it is present in memory 1
    // second bit and third bit is permission level 0,1,2,or 3, 0 for kernel so 00
    // forth bit is always 1
    // fitth bit is if the segment is executable 0
    // sixth bit is if the segment is stack, growing down 0
    // seventh bit is if the segment is readble 1
    // eight bit is if the segment is being acessed by the cpu, Initially set to 0

    unsigned char DATA_FLAG_LIMIT_TOP; // 0xcf; // split half/half flag half limit
    // flags =  1 1 0 0 // Limit = 0xf = 1 1 1 1-> 11001111b = 0xcf
    // first bit granularity
    // second bit is if 16bit or 32 bit

    unsigned char DATA_BASE_TOP; // 0x00;
} __attribute__((packed));

void SET_GDTR(char *srcAdress);

void GET_GDTR(char *destAdress);

void INIT_GDTR(struct GDTR *gdtr);

void INIT_GDT(struct GDT *gdt);
