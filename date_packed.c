#include <stdio.h>
#include <stdint.h>

void NOP()
{
    return;
}

typedef struct datetime_packed_t
{
    // example
    // dt = 14 0a 15 09 30 (hex)
    // dt = 20 10 21 09 48 (dec)

    /**
     * Bitmap of the members. They are ordered in a way that the whole datetime is easily readable
     * as an u32 number. Datetime fields are in descending order, when directly read from memory.
     *
     *          first u16                  second u16
     * bits: 6     4      5+1           5        6        5
     *   +--------------------+  |  +-------------------------+
     *   | year | month | day |  |  | hour | minute | <blank> |
     *   +--------------------+  |  +-------------------------+
     *
     * NOTE: 'day' could be 5 bits long, but +1 dummy bit was added to fill the 16th bit.
    */

    uint16_t day : 6;   // [0, 31] % 64
    uint16_t month : 4; // [0, 12] % 16
    uint16_t year : 6;  // [2000, 2064] % 64

    // ---

    uint16_t blank : 5;
    uint16_t minute : 6; // [0, 59] % 64
    uint16_t hour : 5;   // [0, 24] % 32

} datetime_packed_t;

datetime_packed_t dt = {
    .year = 63,
    // .month = 15,
    .day = 63,

    .hour = 31,
    // .minute = 63,
    .blank = 24};

void main()
{
    uint16_t p[2];

    // read struct as it is in the memory
    p[0] = *((uint16_t *)&dt);
    p[1] = *((uint16_t *)&dt + 1);

    NOP();
}
