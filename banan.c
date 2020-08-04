#include <stdio.h>
#include <stdint.h>

int8_t bin2bcd(uint8_t value)
{
    return (((value / 10) << 4) + (value % 10));
}

uint8_t bcd2bin(uint8_t value)
{
    return (((value & 0xF0) >> 4) * 10 + (value & 0x0F));
}

void main()
{
    uint8_t x = 0x20;
    // helo
    printf("%d --> %d", x, bcd2bin(x));
}