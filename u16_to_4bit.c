#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Shrink an u16 variable into 4 bits of u8.
 */
#define U16_TO_4BIT(u) (uint8_t)(u >> 6)

void main()
{
    char value[] = "3.0";
    char *ptr = value;

    uint8_t temp = atoi(ptr);

    for (uint16_t adc_value = 0; adc_value < 1024; adc_value += 25)
    {
        printf("%d --> %d\n", adc_value, U16_TO_4BIT(adc_value));
    }
}