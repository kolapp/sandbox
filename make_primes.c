#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_prime(uint16_t number)
{
    uint16_t c;

    for (c = 2; c <= number - 1; c++)
    {
        if (number % c == 0)
        {
            return false;
        }
    }
    if (c == number)
    {
        return true;
    }
}

uint16_t get_next_prime()
{
    static uint16_t number = 2;

    // roll it until we find a prime, and return that
    while (1)
    {
        if (is_prime(number))
        {
            return number++;
        }
        else
        {
            number++;
        }
    }
}

void main()
{
    uint8_t prime_u8;

    for (uint16_t n = 0; n < 256; n++)
    {
        printf("%d ", get_next_prime());
    }
}