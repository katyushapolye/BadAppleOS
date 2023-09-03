#ifndef IDT_H
#define IDT_H

#define TRAP_GATE_TYPE 0x8f
#define INTERRUPT_GATE_TYPE 0x8e

struct IDTR
{
    unsigned short int size;
    unsigned long int base;

} __attribute__((packed));
// diffent from the GDT, as we need to put registries and

struct IDT_GATE
{
    unsigned short int OFFSET_LOW; // low(0:16) memory offset of where the Interrupt handling routine is
    unsigned short int SEG_SELECTOR;
    // SEGMENT SELECTOR 15:3 = INDEX,OF THE SEG, LOWER 3 BITS ARE 0 so only
    // 2 = TI-> 0 is GDT and 1 is IDT
    //  EN 1:0 Is RPL
    unsigned char ZERO; // always zero
    unsigned char TYPE; // Type of interrups and some other flags
    // bytes
    // 0:3 Gate type
    //  0x5 32-bit task gate ->not used
    //  0xe interrupt gate ->used for hardware
    // -0xf trap gate ->used for excpetion

    // 4 -> storage seg, set 0 for interrupts gate

    // 5:6 -> privilege, 0 for kernel, so 0x0

    // 7: present, always 1 for active

    // so we have in normal interrupts is
    // 1 0 0 0 1 1 1 0 = 0x8e?

    // and for exception is
    // only changes the type wich is 0xf = 1111
    // and as such
    // 1 0 0 0 1 1 1 1 = 0x8f

    unsigned short int OFFSET_HIGH; // High memoru offset of where our interrupt routine is
} __attribute__((packed));

// The things we shall push into the stack for the iretq instruction to restore
// Is on some manual of intel what the CPU pushes into the stack
typedef struct
{
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
    unsigned int sp;
    unsigned int ss;

} __attribute__((packed)) INTERRUPT_FRAME;

// Default exception handler for non returning error codes
__attribute((interrupt)) void DEFAULT_EXCEPT_HANDLER(INTERRUPT_FRAME *context);

// Default exception handler for returning error codes
__attribute((interrupt)) void DEFAULT_EXCEPT_HANDLER_ERROR_CODE(INTERRUPT_FRAME *context, unsigned int erroCode);

__attribute((interrupt)) void DEFAULT_INTERRUPT(INTERRUPT_FRAME *context);

void SET_IDTR(char *srcAdress);
void GET_IDTR(char *destAdress);

int GET_IDT_BASE_ADRESS();

// The segment is always the same, as we only have one seg for code
void INIT_GATE(struct IDT_GATE *IDTbaseAdress, int index, void *isr, short int type);

void INIT_IDT(void);
#endif