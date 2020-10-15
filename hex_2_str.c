#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void hex_to_string(uint8_t *hex, uint8_t length, char *hex_str)
{
    /**
     * NOTE: 'len' amount of numbers will produce (len * 2 + 1) characters.
     * Example: [0xCA, 0xFE] --> ['C', 'A', 'F', 'E', '\0']
     */

    char digits[2];
    uint8_t nibble;

    // making sure hex_str is null terminated, so strcat will work properly
    *hex_str = '\0';

    // loop numbers
    for (uint8_t n = 0; n < length; n++)
    {
        // get nibble from number
        nibble = hex[n] >> 4;

        // loop digits
        for (uint8_t i = 0; i < 2; i++)
        {
            // is it 0-9?
            if (nibble < 0x0A)
            {
                digits[i] = nibble + '0';
            }
            // is it A-F?
            else if ((nibble >= 0x0A) && (nibble <= 0x0F))
            {
                digits[i] = nibble + '0' + 7;
            }
            else
            {
                digits[i] = 0;
            }

            // get the other nibble from number
            nibble = hex[n] & 0x0F;
        }

        // 2 digits are done, append them
        strncat(hex_str, digits, 2);
    }
}

void main()
{
    uint8_t input[32] = {0xde, 0xad, 0xbe, 0xef};
    char output[64];

    hex_to_string(input, 4, output);
    printf("%s\n", output);
}