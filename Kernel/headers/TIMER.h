#ifndef TIMER_H
#define TIMER_H
#define TIME_DATA_ADRESS 0x820 // not decied yet
#define PIT__BASE_FREQ 1193182
#define PIT_INTERVAL 1

struct TIMERDATA
{
    unsigned int SYS_TIME;    // 4 bytes
    unsigned int TARGET_TIME; // 4 bytes
    unsigned int PADDING;     // 4 byres of 1, we might use it for error correction
    unsigned int IS_HALTED;   // 4 bytesn ALL 1 IF YES, ALL 0 IF NOT

} __attribute((packed)); // sze = 0x10 = 16 bytes

// Resets the system timer, does not start it if halted
void RESET_SYSTEM_TIME();

// Gets the time elapsed since last reset (in ms), Note that, it overflows in around 49 days of uptime
unsigned int GET_SYSTEM_TIME();

// Halts the system timer
void HALT_SYSTEM_TIME();

// Returns the system timer from the halt state
void START_SYSTEM_TIME();

// Sleeps the machine for sleepTime ms, if blockIT is true, it also masks interrupts (apart from the PIT because if it is masked well...then we dont return from the sleep)
void SLEEP(unsigned int sleepTime, char blockIT);

// Used by the PIT interrupt for incrementing the timer
void TICK_TIME();

#endif