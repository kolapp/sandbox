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

bool is_prime_faster(uint16_t number)
{
    uint16_t c;

    if (number <= 1)
    {
        return false;
    }
    else if ((number % 2 == 0) && (number > 2))
    {
        return false;
    }

    for (int c = 3; c < number / 2; c += 2)
    {
        if (number % c == 0)
            return false;
    }
    return true;

    // https://stackoverflow.com/questions/5281779/c-how-to-test-easily-if-it-is-prime-number
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

    // simply make primes
    // for (uint16_t n = 0; n < 256; n++)
    // {
    //     printf("%d ", get_next_prime());
    // }

    // mjake primes and shrink them into an u8
    for (uint16_t n = 0; n < 30 * 8; n++)
    {
        prime_u8 = (uint8_t)get_next_prime();
        if (n % 8 == 0)
            printf("\n");
        printf("%02X ", prime_u8);
    }
}