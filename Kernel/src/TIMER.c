#include "../headers/TIMER.h"

struct TIMERDATA *tData = TIME_DATA_ADRESS;

void RESET_SYSTEM_TIME()
{
    tData->SYS_TIME = 0;
};

unsigned int GET_SYSTEM_TIME()
{
    return tData->SYS_TIME;
}

void TICK_TIME()
{

    tData->SYS_TIME += PIT_INTERVAL;
}

void START_SYSTEM_TIME()
{
    tData->IS_HALTED = 0x00000000;
}

void HALT_SYSTEM_TIME()
{
    tData->IS_HALTED = 0xffffffff;
}