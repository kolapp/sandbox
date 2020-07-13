#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define LOWER4BIT(x) x & 0x0F
#define UPPER4BIT(x) (x << 4) & 0xF0
#define TWD_SIZE 16
#define RING_SIZE 6

uint8_t IN0_write_ptr = 1;

typedef struct
{
    uint8_t write_ptr;
    uint8_t data[TWD_SIZE];
} twd_t;

void main()
{
    int i;
    uint8_t temp;
    srand(time(NULL));

    // init
    twd_t twd;
    twd.write_ptr = 0;

    // 4 bit array implementation
    for (i = 0; i < TWD_SIZE; i++)
    {
        // clear before writing into
        twd.data[twd.write_ptr] = 0;

        // lower 4 bit
        temp = 0x0A;
        twd.data[twd.write_ptr] |= LOWER4BIT(temp);

        // upper 4 bit
        temp = 0x0B;
        twd.data[twd.write_ptr] |= UPPER4BIT(temp);

        twd.write_ptr++;
    }

    for (i = 0; i < twd.write_ptr; i++)
    {
        printf("%x, ", twd.data[i]);
    }
}