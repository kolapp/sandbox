#include <stdio.h>
#include <stdint.h>

#define RB_SIZE 6

uint8_t read_ptr = 0;
uint8_t write_ptr = 1;
uint8_t number_of_items;

uint8_t i, j;

uint8_t get_number_of_items(uint8_t w, uint8_t r)
{
    uint8_t x;

    // by Atilla, helyesen mukodik
    if (r > w)
    {
        x = RB_SIZE - 1 - (r - w);
    }
    else
    {
        x = (w - r) - 1;
    }

    // ezekre hibas, minden masra jo
    // w0, r0 ==> 255
    // w0, r1 ==> 0
    // w0, r2 ==> 1
    // w0, r3 ==> 2
    // w0, r4 ==> 3
    // w0, r5 ==> 4
    // if (w > r)
    // {
    //     x = ((w - r) % RB_SIZE - 1) % RB_SIZE;
    // }
    // else
    // {
    //     x = ((r - w) % RB_SIZE - 1) % RB_SIZE;
    // }

    // ez is kaka
    // if (r > w)
    // {
    //     x = RB_SIZE - 1 - (r - w);
    // }
    // else
    // {
    //     x = RB_SIZE - 1 - (w - r);
    // }

    // kaka
    // x = w - r;
    // x %= RB_SIZE;
    // x -= 1;
    // x %= RB_SIZE;

    // ez is kaka
    // x = (w - r - 1) % RB_SIZE;

    // valami kaka ebben
    // x = ((w - r) % RB_SIZE - 1) % RB_SIZE;

    // invalid state
    if (w == r)
    {
        return 255;
    }

    return x;
}

void main()
{
    // test for all inputs
    for (i = 0; i < RB_SIZE; i++)
    {
        for (j = 0; j < RB_SIZE; j++)
        {
            printf("w%d, r%d ==> %d\n", i, j, get_number_of_items(i, j));
        }
        printf("\n");
    }
}