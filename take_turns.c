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
#include <stdbool.h>
#include <time.h>

#define MAX_SOUPS_SERVED 4
// number of cases
#define NUMBER_OF_GUESTS 5
// [0, 100]
#define SOUP_CHANCE 80

// -------------------------------------------------------------------------------------------------

// This should have exactly <NUMBER_OF_GUESTS> members.
typedef enum Guests
{
    GUEST_0,
    GUEST_1,
    GUEST_2,
    GUEST_3,
    GUEST_4,
} guests_t;

typedef enum
{
    NOPE,
    YES,
} soup_status_t;

// -------------------------------------------------------------------------------------------------

soup_status_t get_soup(guests_t guest)
{
    printf("#%d asks for soup.\n", guest);

    // some guests always gets soup, some dont
    switch (guest)
    {
    case GUEST_0:
    case GUEST_1:
    case GUEST_4:
        return YES;

    case GUEST_2:
    case GUEST_3:
        return NOPE;

    default:
        printf("What the hell? Unknown guest: %d\n", guest);
        return NOPE;
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

bool take_turns(void)
{
    // does the guest get soup?
    static soup_status_t soup_status;
    // who comes next?
    static guests_t turn = 0;
    // how many guests GOT served soup?
    static uint8_t soups_served = 0;
    // its possible to ask twice for soup, if nobody else got soup (special case)
    static uint8_t repeta;
    // did the guest eat soup?
    bool is_successful = false;

    /**
     * What happens here:
     *  + loop over the guests enum
     *  + the loop increments with each function call, sometimes by more than 1
     *
     *  + count how many guests eat soup
     *  + number of soups is limited, start over if soup limit is reached
     */

    // ran out of soup!
    // this happens when there are lot more guests than soups
    if (soups_served >= MAX_SOUPS_SERVED)
    {
        turn = 0;
        soups_served = 0;

        printf("Served all %d of the soups! Starting over from zero.\n\n", MAX_SOUPS_SERVED);
    }

    // guest asks for soup
    // stop looping when 1 soup is served OR reached the attempt limit
    repeta = 0;
    while (1)
    {
        // dont loop forever
        if (repeta > 1)
        {
            return false;
        }

        soup_status = get_soup(turn);
        if (soup_status == YES)
        {
            eat_soup(turn);

            soups_served++;
            is_successful = true;
        }

        // next one comes in line, whether the guest got soup or not
        turn++;
        if (turn >= NUMBER_OF_GUESTS)
        {
            turn = 0;

            // whatever number of soups got served until this point,
            // starting from guest 0 means a fresh start
            soups_served = 0;

            // give guests a 2nd chance, if nobody ate soup
            repeta++;
            printf("Repeta time.\n");
        }

        // soup got served, we are done
        if (is_successful)
        {
            return true;
        }
    } // while
}

// -------------------------------------------------------------------------------------------------

void main()
{
    srand(time(0));

    for (uint8_t serving = 0; serving < 12; serving++)
    {
        // simulate XY minutes of wait, just for show
        system("timeout 1 >> NULL");
        // show some made-up time for immersion, just for show
        printf("\n--- time is %02d:%02d ---\n", 11 + (serving * 5) / 60, (serving * 5) % 60);

        // !!!
        take_turns();
    } // for

} // main