#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
    NOTHING,
    OK,
} status_t;

status_t read_something()
{
    if ((rand() % 100) > 40)
    {
        return OK;
    }
    else
    {
        return NOTHING;
    }
}

void main()
{
    srand(time(0));

    // result of some reading
    uint8_t status;
    // who comes next?
    uint8_t turn = 0;

    for (uint8_t n = 0; n < 16; n++)
    {

        switch (turn)
        {
        case 0:
            status = read_something();
            if (status == OK)
            {
                printf("zero works\n");
            }
            break;

        case 1:
            status = read_something();
            if (status == OK)
            {
                printf("one works\n");
            }
            break;

        case 2:
            status = read_something();
            if (status == OK)
            {
                printf("two works\n");
            }
            break;

        case 3:
            status = read_something();
            if (status == OK)
            {
                printf("three works\n");
            }
            break;
        default:
            break;
        }

        turn++;
        if (turn > 3)
        {
            printf("- - - - - -\n");
            turn = 0;
        }
    }
}