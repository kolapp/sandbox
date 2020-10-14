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

#define MAX_SOUPS_SERVED 5
// number of cases
#define NUMBER_OF_GUESTS 3
// [0, 100]
#define SOUP_CHANCE 100

// This should have exactly <NUMBER_OF_GUESTS> members.
typedef enum Guests
{
    Zero,
    One,
    Two,
} guests_t;

typedef enum
{
    NOPE,
    YES,
} soup_status_t;

soup_status_t get_soup(guests_t guest)
{
    /*
    // Zero is sneaky and always gets soup
    if (guest == Zero)
    {
        return YES;
    }
    */

    // others have a random chance of getting soup
    if ((rand() % 100) <= SOUP_CHANCE)
    {
        return YES;
    }
    else
    {
        return NOPE;
    }
}

void eat_soup(guests_t guest)
{
    switch (guest)
    {
    case Zero:
        printf("Zero is eating.\n");
        break;

    case One:
        printf("One is eating.\n");
        break;

    case Two:
        printf("Two is eating.\n");
        break;

    default:
        break;
    }
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

    // guests_t guest = 0;

    for (uint8_t serving = 0; serving < 16; serving++)
    {
        // simulate XY minutes of wait, just for show
        system("timeout 1 >> NULL");

        // all guests asked for soup
        if (turn >= NUMBER_OF_GUESTS)
        {
            turn = 0;
            soups_served = 0;

            printf("Asked all %d guests for soup.\n\n", NUMBER_OF_GUESTS);
        }

        // ran out of soup!
        if (soups_served >= MAX_SOUPS_SERVED)
        {
            turn = 0;
            soups_served = 0;

            printf("Served all %d of the soups, come back later.\n\n", MAX_SOUPS_SERVED);
        }

        // guest asks for soup
        while (turn < NUMBER_OF_GUESTS)
        {
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
        } // while
    }     // for

} // main