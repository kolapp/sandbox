#include <stdio.h>
#include <stdint.h>

/** 
 * Replace (0, ..., 0) series of zero numbers to a (0, <number of zeros>) pair. Non-zero numbers
 * are unchanged. The compressed array can be decoded without data loss.
 *
 * @param [in] input: Number array to be compressed.
 * @param [in] input_length: Length of input array.
 * @param [out] compressed: Compressed version of input array. This should be 
 * around 1.5x size of the input array. In the worst case scenario, output is bigger than the input.
 * @retval Length of 'compressed' array.
 *
 * Example Usage:
 * @code
 * uint8_t arr[] = {1, 0, 0, 0, 4, 0, 0, 0};
 * uint8_t result[32];
 * uint8_t result_size;
 * result_size = compress_zeros(arr, 8, result);
 * // result == {1, 0, 3, 4, 0, 3}
 * @endcode
 */
uint8_t compress_zeros(uint8_t *input, uint8_t input_length, uint8_t *compressed)
{
    // zero counter
    uint8_t cnt = 0;

    // pointer used to write into the output array
    // NOTE: this could be removed, its only really neccessary for calculating the output array size
    uint8_t *out = compressed;

    // loop the input array
    for (uint8_t *n = input; n < (input + input_length); n++)
    {
        // NOTE: *n is the current input value
        // keep counting zeros until a non-zero item comes
        if (*n == 0x00)
        {
            cnt++;
        }
        // non-zero
        else
        {
            // was zero before: [... 0 N]
            if (cnt == 0)
            {
                // append the number as is
                *out++ = *n;
                // NOTE: the instruction above is shorthand for *out = *n; out++;
            }
            // was no zero before: [... N]
            else
            {
                // append (0, #zeros, some-number)
                *out++ = 0x00;
                *out++ = cnt;
                *out++ = *n;

                cnt = 0;
            }
        }
    }
    // last item was zero: [... 0]
    if (cnt != 0)
    {
        // append (0, #zeros)
        *out++ = 0x00;
        *out++ = cnt;
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

// uint8_t arr[] = {0, 0, 0, 0, 0, 0, 0, 7, 5, 0, 0, 10, 0};
// out = {0, 7, 7, 5, 0, 2, 10, 0, 1};

// uint8_t arr[] = {0, 7, 5};
// out = {0, 1, 7, 5};

// uint8_t arr[] = {8, 9, 3, 4, 5, 6, 2, 3, 5, 6};
// out = {8, 9, 3, 4, 5, 6, 2, 3, 5, 6};

uint8_t arr[] = {1, 0, 0, 0, 4, 0, 0, 0};
// out = {1, 0, 3, 4, 0, 3};

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