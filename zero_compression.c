#include <stdio.h>
#include <stdint.h>

uint8_t compress_zeros(uint8_t *input, uint8_t input_length, uint8_t *compressed)
{
    uint8_t cnt = 0;
    uint8_t *out = compressed;

    for (uint8_t *n = input; n < (input + input_length); n++)
    {
        // zero
        if (*n == 0x00)
        {
            cnt++;
        }
        // non zero
        else
        {
            // was zero before: [... 0 N]
            if (cnt == 0)
            {
                *out = *n;
                out++;
            }
            // was no zero before: [... N]
            else
            {
                *out = 0x00;
                out++;

                *out = cnt;
                out++;

                *out = *n;
                out++;

                cnt = 0;
            }
        }
    }
    // last item was zero: [... 0]
    if (cnt != 0)
    {
        *out = 0x00;
        out++;

        *out = cnt;
        out++;

        // cnt = 0;
    }

    // length of the compressed array
    return (out - compressed);
}

void NOP()
{
    return;
}

// ---
// real test examples

// uint8_t arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
// out = ?

// uint8_t arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0};
// out = ?

// uint8_t arr[] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1};
// out = ?

// uint8_t arr[] = {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 0};
// out = ?

// ---
// baked test examples

uint8_t arr[] = {0, 0, 0, 0, 0, 0, 0, 7, 5, 0, 0, 10, 0};
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

uint8_t result[32];

uint8_t result_size;

void main()
{
    // a quick heuristic to test if its worth compressing
    uint8_t count_zero_n = 0;
    uint8_t count_zeros = 0;

    for (uint8_t i = 0; i < arr_size - 1; i++)
    {
        if (arr[i] == 0)
        {
            // increment if encountering a (0, non-zero) pair,
            // check ((NOT A) AND B) truth table to verify
            count_zero_n += (!arr[i] && arr[i + 1]);

            count_zeros++;
        }
    }

    NOP();

    result_size = compress_zeros(arr, arr_size, result);

    NOP();
}