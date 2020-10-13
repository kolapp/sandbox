/**
 * This silly code is used to test scheduling for sending metering data on the LoRa mote.
 *
 * Guests are measured metering systems.
 *
 * Soups mean the given metering system has useful data to send.
 *
 * Max soups mean that only a limited amount of metering systems should be able to send data.
 *
 * Random chance is used to indicate whether a metering system has data to send, is available
 * or connected at all.
 *
 * A day means a certain time interval the mote has to send out the most possible data.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SOUPS_SERVED 2
// number of cases
#define NUMBER_OF_GUESTS 4
// [0, 100]
#define SOUP_CHANCE 40

typedef enum
{
    NOPE,
    YES,
} soup_status_t;

soup_status_t get_soup()
{
    // random chance of getting soup
    if ((rand() % 100) < SOUP_CHANCE)
    {
        return YES;
    }
    else
    {
        return NOPE;
    }
}

void main()
{
    srand(time(0));

    // does the guest get soup?
    soup_status_t soup_status;
    // who comes next?
    uint8_t turn = 0;
    // how many guests GOT served soup?
    uint8_t soups_served = 0;

    // 1 iteration means 1 guest asking for soup
    for (uint8_t n = 0; n < 16; n++)
    {
        // all guests asked for soup
        if (turn >= NUMBER_OF_GUESTS)
        {
            turn = 0;
            soups_served = 0;
            printf("\n> The next day:\n");
        }

        // ran out of soup!
        if (soups_served >= MAX_SOUPS_SERVED)
        {
            turn = 0;
            soups_served = 0;

            printf("Served all the soups (that is %d), come back tomorrow.\n", MAX_SOUPS_SERVED);
            printf("\n> The next day:\n");
        }

        // guest next in line asks for soup
        switch (turn)
        {
        case 0:
            soup_status = get_soup();
            if (soup_status == YES)
            {
                soups_served++;
                printf("zero is eating.\n");
            }
            break;

        case 1:
            soup_status = get_soup();
            if (soup_status == YES)
            {
                soups_served++;
                printf("one is eating.\n");
            }
            break;

        case 2:
            soup_status = get_soup();
            if (soup_status == YES)
            {
                soups_served++;
                printf("two is eating.\n");
            }
            break;

        case 3:
            soup_status = get_soup();
            if (soup_status == YES)
            {
                soups_served++;
                printf("three is eating.\n");
            }
            break;
        default:
            break;
        }

        // move to next guest
        turn++;
    }
}