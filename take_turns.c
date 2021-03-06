/**
 * This silly code is used to test scheduling for sending metering data on the LoRa mote.
 *
 * Guests are measured metering systems.
 *
 * Soups mean the given metering system has useful data to send.
 *
 * Max soups mean that only a limited amount of metering systems should be able to send data.
 *
 * Random chance is used to indicate the uncertainty whether a metering system has data to send,
 * is available or connected at all.
 *
 * A serving means an XY minute long timespan and can result in 1 served soup.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SOUPS_SERVED 4
// number of cases
#define NUMBER_OF_GUESTS 5
// [0, 100]
#define SOUP_CHANCE 80

// This should have exactly <NUMBER_OF_GUESTS> members.
typedef enum Guests
{
    Zero,
    One,
    Two,
    Three,
    Four,
} guests_t;

typedef enum
{
    NOPE,
    YES,
} soup_status_t;

soup_status_t get_soup(guests_t guest)
{
    printf("#%d asks for soup.\n", guest);

    // some guests always gets soup
    switch (guest)
    {
    case Zero:
    case One:
        return YES;
        // return NOPE;
        break;

    case Two:
    case Three:
        // return YES;
        return NOPE;
        break;

    case Four:
        return YES;
        // return NOPE;

    default:
        break;
    }

    /*
    //random chance of getting soup
    if ((rand() % 100) <= SOUP_CHANCE)
    {
        return YES;
    }
    else
    {
        return NOPE;
    }
    */
}

void eat_soup(guests_t guest)
{
    printf("#%d is eating.\n", guest);
}

void main()
{
    srand(time(0));

    // does the guest get soup?
    soup_status_t soup_status;
    // who comes next?
    guests_t turn = 0;
    // how many guests GOT served soup?
    uint8_t soups_served = 0;
    // its possible to ask twice for soup, if nobody else got soup (special case)
    uint8_t repeta;

    // guests_t guest = 0;

    for (uint8_t serving = 0; serving < 12; serving++)
    {
        // simulate XY minutes of wait, just for show
        system("timeout 1 >> NULL");
        // show some made-up time for immersion, just for show
        printf("\n--- time is %02d:%02d ---\n", 11 + (serving * 5) / 60, (serving * 5) % 60);

        // all guests asked for soup
        // dead code?
        // if (turn >= NUMBER_OF_GUESTS)
        // {
        //     turn = 0;
        //     soups_served = 0;

        //     printf("All %d guests asked for soup. Time to eat again.\n", NUMBER_OF_GUESTS);
        // }

        // ran out of soup!
        if (soups_served >= MAX_SOUPS_SERVED)
        {
            turn = 0;
            soups_served = 0;

            printf("Served all %d of the soups, come back later.\n\n", MAX_SOUPS_SERVED);
        }

        // guest asks for soup
        repeta = 0;
        while (1)
        {
            if (repeta > 1)
            {
                // go home now y'all
                break;
            }
            soup_status = get_soup(turn);

            if (soup_status == YES)
            {
                soups_served++;
                eat_soup(turn);
                // next one comes in line ...
                turn++;

                break;
            }
            // ... whether the guest got soup or not
            turn++;

            if (turn >= NUMBER_OF_GUESTS)
            {
                turn = 0;
                soups_served = 0;

                repeta++;
                printf("Repeta time.\n");
            }
        } // while
    }     // for

} // main