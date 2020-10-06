#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/**
* More readable string comparison.
* @retval 1 if a == b, otherwise 0.
*/
#define STR_IS_EQUAL(a, b) (strcmp(a, b) ? 0 : 1)

char line[16] = "egy=sajt";
// char line[16] = "ketto=2";

// pointer to the first character of the first token
char *key;
char *value;

uint8_t x;

void NOP()
{
    return;
}

void main()
{
    key = strtok(line, "=");
    // For subsequent calls to strtok(), s1 should be set to a NULL.
    value = strtok(NULL, "=");

    NOP();

    // case: "egy"
    if STR_IS_EQUAL (key, "egy")
    {
        NOP();
        // ...
    }
    // case: "ketto"
    else if STR_IS_EQUAL (key, "ketto")
    {
        x = atoi(value);
        // ...
    }
    // default case
    else
    {
        NOP();
        // ...
    }
}