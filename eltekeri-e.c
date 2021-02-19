#include <stdio.h>
#include <stdint.h>

void teker(uint8_t *pt)
{
    printf("%d ", *pt);
    pt++;

    printf("%d ", *pt);
    pt++;

    printf("%d ", *pt);
    pt++;

    return;
}

uint8_t arr[4] = {1, 2, 3, 4};

void main()
{
    uint8_t *pt = arr;

    *pt++ = 10;
    *pt++ = 20;
    *pt++ = 30;
    *pt++ = 40;

    teker(arr);
    // nem tekeri el

    return;
}