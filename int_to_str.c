#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void decimal_u8_to_str(uint8_t number, char *digits)
{
    uint8_t i;
    uint8_t temp;

    // zero seems a bit special
    if (!number)
    {
        digits[0] = '0';
        digits[1] = '\0';
        return;
    }

    // an u8 can be max 3 digits + '0', that is 4 chars
    for (i = 0; i < 4; i++)
    {
        // no more digits
        if (!number)
        {
            // terminate the string
            digits[i] = '\0';

            // digits are placed in reverse order, so reverse them (again) in a very simple way
            if (i == 2)
            {
                // number is 2 long, switch digit 0, 1
                temp = digits[0];
                digits[0] = digits[1];
                digits[1] = temp;
            }
            else if (i == 3)
            {
                // number is 3 long, switch digit 0, 2
                temp = digits[0];
                digits[0] = digits[2];
                digits[2] = temp;
            }

            return;
        }

        // store digit and convert number to char
        digits[i] = (number % 10) + '0';
        // go to next digit
        number /= 10;
    }
}

void main()
{
    char digits[6];
    uint8_t number;

    for (number = 0; number < 255; number++)
    {
        decimal_u8_to_str(number, digits);
        printf("%d == '%s'\n", number, digits);
    }
}