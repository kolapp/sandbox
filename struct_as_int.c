#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct TASKS_t
{
    uint8_t IN0 : 1;
    uint8_t IN1 : 1;
    uint8_t IN2 : 1;
    uint8_t IN3 : 1;
    uint8_t TMR0 : 1;
    // RTC alarm happenning every minute, or how RTC alarm is configured.
    uint8_t RTC_ALM : 1;
    uint8_t TIMED_TASK_X_MIN : 1;
    // ...

} TASKS_t;

void NOP()
{
    return;
}

uint8_t aux;
void main()
{
    volatile TASKS_t TASKS = {
        .IN0 = 1,
        .IN1 = 0,
        .IN2 = 0,
        .IN3 = 0,
        .TMR0 = 0,
        .RTC_ALM = 0,
        .TIMED_TASK_X_MIN = 0};

    // TASKS.RTC_ALM = 1;
    // TASKS.TIMED_TASK_X_MIN = 1;

    aux = *((uint8_t *)&TASKS);
    if (aux == 0)
    {
        NOP();
    }

    NOP();
}