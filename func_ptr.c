#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// DUMMY
typedef struct ring_buf_item_t
{
    const uint8_t meter_id;
} ring_buf_item_t;

// DUMMY
void FRAM_append_data(uint8_t data, ring_buf_item_t *rbi)
{
    printf("appending '%02X' for meter #%d\n", data, rbi->meter_id);
}
// -------------------------------------------------------------------------------------------------

typedef void (*fram_data_handler)(uint8_t, ring_buf_item_t *);

void wrapper(fram_data_handler func, uint8_t data, ring_buf_item_t *rbi)
{
    printf("> will run func()\n");
    func(data, rbi);
    printf("> done.\n");
}

void main()
{
    fram_data_handler handler;

    ring_buf_item_t rb = {
        .meter_id = 3};

    // simple function pointer
    handler = FRAM_append_data;
    if (handler)
    {
        handler(0xCA, &rb);
    }

    // function with a function ptr argument
    wrapper(FRAM_append_data, 0xFE, &rb);
}