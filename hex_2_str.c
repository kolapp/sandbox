#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void hex_to_chars(uint8_t hex, char *hex_str)
{
    uint8_t nib;

    // mask nibble
    nib = hex >> 4;

    for (uint8_t n = 0; n < 2; n++)
    {
        // is it 0-9?
        if (nib < 0x0A)
        {
            hex_str[n] = nib + '0';
        }
        // is it A-F?
        else if ((nib >= 0x0A) && (nib <= 0x0F))
        {
            hex_str[n] = nib + '0' + 7;
        }
        else
        {
            hex_str[n] = 0;
        }

        // switch to other nibble
        nib = hex & 0x0F;
    }

    hex_str[2] = '\0';
}

void main()
{
    uint8_t input[32] = {0xde, 0xad, 0xbe, 0xef};
    char output[64];
    char chars[3];

    char *s1;
    char *s2;

    output[0] = '\0';

    s1 = output;
    s2 = chars;

    for (uint8_t n = 0; n < 4; n++)
    {
        hex_to_chars(input[n], s2);
        strncat(s1, s2, 2);
    }

    printf("'%s'\n", output);
}