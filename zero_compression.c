#include <stdio.h>
#include <stdint.h>

void compress(uint8_t *input, uint8_t *compressed)
{
}

void NOP()
{
    return;
}

void main()
{
    // test examples

    // ---
    // real

    uint8_t arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
    // out = ...

    // uint8_t arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0};
    // out = ...

    // uint8_t arr[] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1};
    // out = ...

    // uint8_t arr[] = {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 0};
    // out = ...

    // ---
    // baked

    // uint8_t arr[] = {0, 0, 0, 0, 0, 0, 0, 7, 5, 0, 0, 10, 0};
    // out = {0, 7, 7, 5, 0, 2, 10, 0, 1};

    // uint8_t arr[] = {0, 7, 5};
    // out = {0, 1, 7, 5};

    // uint8_t arr[] = {8, 9, 3, 4, 5, 6, 2, 3, 5, 6};
    // out = {8, 9, 3, 4, 5, 6, 2, 3, 5, 6};

    // uint8_t arr[] = {1, 3, 0, 0, 4, 0, 0, 0};
    // out = {1, 3, 0, 2, 4, 0, 3};

    // uint8_t arr[] = {1, 0, 2, 0, 3, 0, 4, 0, 5, 0};
    // out = {1, 0, 1, 2, 0, 1, 3, 0, 1, 4, 0, 1, 5, 0, 1};

    uint8_t arr_size = sizeof(arr) / sizeof(uint8_t);

    // ---

    // a quick heuristic to test if its worth compressing
    uint8_t count_zero_n = 0;

    for (uint8_t i = 0; i < arr_size - 1; i++)
    {
        // increment if encountering a (0, non-zero) pair,
        // check ((NOT A) AND B) truth table to verify
        count_zero_n += (!arr[i] && arr[i + 1]);
    }

    NOP();
}