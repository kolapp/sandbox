#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// -------------------------------------------------------------------------------------------------

/**
 * Starting address of ring buffer data. 
 *
 * Addresses in [0, RB_DATA_OFFSET) are reserved for persistent parameters, state variables, etc. 
 * Also this number is the size of space for those persistent data. 
 * NOTE: Make sure to choose a size that the fields in 'global_params' enum fit here! 
 * NOTE: Never set this to 0, the program will overwrite its state variables and behave randomly. 
 */
#define RB_DATA_OFFSET 10
// #define RB_DATA_OFFSET 200

/**
 * Ring buffer parameter block size (bytes). 
 * Make sure its big enough to store all fields found in 'RB_address' enum.
 */
#define RB_PARAM_SIZE 7

/**
 * Ring buffer useful data block size (bytes). This holds (RB_DATA_SIZE x 2) minutes of 
 * impulse data. 
 */
#define RB_DATA_SIZE 1

// Number of items one ring buffer.
#define RB_NUM_ITEMS 3

// Size of one ring buffer item (bytes).
#define RB_ITEM_SIZE (RB_PARAM_SIZE + RB_DATA_SIZE)
// Size of one ring buffer (bytes).
#define RB_SIZE (RB_NUM_ITEMS * RB_ITEM_SIZE)

// -------------------------------------------------------------------------------------------------

// FRAM addresses of ring buffer global parameters and other important persistent data.
enum global_params
{
    // IN0 write index FRAM address (1 byte)
    RB_ADDR_IN0_WR_I,
    // IN0 read/send index FRAM address (1 byte)
    RB_ADDR_IN0_RD_I,

    // IN1 write index FRAM address (1 byte)
    RB_ADDR_IN1_WR_I,
    // IN1 read/send index FRAM address (1 byte)
    RB_ADDR_IN1_RD_I,

    // IN2 write index FRAM address (1 byte)
    RB_ADDR_IN2_WR_I,
    // IN2 read/send index FRAM address (1 byte)
    RB_ADDR_IN2_RD_I,

    // IN3 write index FRAM address (1 byte)
    RB_ADDR_IN3_WR_I,
    // IN3 read/send index FRAM address (1 byte)
    RB_ADDR_IN3_RD_I,
};

// Parameter index mapping inside the ring buffer, number of elements must be in [0, RB_PARAM_SIZE).
// These are indexes, not memory addresses!
enum RB_address
{
    // Inner data block write pointer in a ring buffer item
    RB_INNER_PTR,
    // Starting index of T0
    RB_T0_YR,
    RB_T0_MTH,
    RB_T0_DAY,
    RB_T0_HR,
    RB_T0_MIN,
    RB_T0_SEC,
};

// -------------------------------------------------------------------------------------------------
typedef enum meters_type_t
{
    // NOTE: Dont offset the members, start from 0. Multiple code parts depend on this.

    // TODO:
    // // Water meter impulse connected to IN0 pin.
    METER_IN0,
    // Water meter impulse connected to IN1 pin.
    METER_IN1,
    // // Water meter impulse connected to IN2 pin.
    METER_IN2,
    // // Water meter impulse connected to IN3 pin.
    METER_IN3,
} meters_type_t;

/**
 * Necessary variables to read/write the ring buffer in different contexts.
 */
typedef struct ring_buf_item_t
{
    // Base datetime for measurements.
    uint8_t T0[6];

    // Ring buffer write index.
    uint8_t write_ptr;
    // Ring buffer read/send index.
    uint8_t send_ptr;
    // Ring buffer write index FRAM address.
    const uint32_t write_ptr_addr;
    // Ring buffer read/send index FRAM address.
    const uint32_t send_ptr_addr;
    // ...
    // NOTE: type is meters_type_t, but value should be IN0..IN3, and not MB_xyz.
    const meters_type_t meter_id;

    // Upper + lower nibble of data stored here.
    uint8_t temp_data;
    // Index used inside a ring buffer block. Points to where last data was written.
    uint8_t inner_i;
    // Upper/lower nibble write select bit.
    bool nibble_select;
} ring_buf_item_t;

// -------------------------------------------------------------------------------------------------

/**
 * Get the starting address of i-th ring buffer data block
 * @param [in] index
 * @retval ...
 */
#define INDEX_TO_FRAM_DATA_ADDR(i, in_x) ((i * RB_ITEM_SIZE + RB_PARAM_SIZE) + (in_x * RB_SIZE) + RB_DATA_OFFSET)

/**
 * Get the starting address of i-th ring buffer parameter block
 * @param [in] index
 * @retval ...
 */
#define INDEX_TO_FRAM_PARAM_ADDR(i, in_x) ((i * RB_ITEM_SIZE) + (in_x * RB_SIZE) + RB_DATA_OFFSET)

/**
 * Shrink an 8 bit variable into its lower 4 bits
 * @param [in] x uint8_t
 * @retval ...
 *
 * Example Usage:
 * @code
 * temp = 0xCA;
 * data |= LOWER4BIT(temp);
 * // data == 0x0A
 * @endcode
 */
#define LOWER4BIT(x) (x & 0x0F)

/**
 * Shrink an 8 bit variable into its upper 4 bits
 * @param [in] x uint8_t
 * @retval ...
 *
 * Example Usage:
 * @code
 * temp = 0xFE;
 * data |= UPPER4BIT(temp);
 * // data == 0xE0
 * @endcode
 */
#define UPPER4BIT(x) ((x << 4) & 0xF0)

void NOP()
{
    return;
}

// -------------------------------------------------------------------------------------------------

// Ring buffer context variable for IN0.
ring_buf_item_t rb_in0 = {
    .write_ptr = 1,
    .send_ptr = 0,
    .write_ptr_addr = (uint32_t)RB_ADDR_IN0_WR_I,
    .send_ptr_addr = (uint32_t)RB_ADDR_IN0_RD_I,
    .meter_id = METER_IN0,
    .temp_data = 0,
    .inner_i = 0,
    .nibble_select = false};

// Ring buffer context variable for IN1.
ring_buf_item_t rb_in1 = {
    .write_ptr = 1,
    .send_ptr = 0,
    .write_ptr_addr = (uint32_t)RB_ADDR_IN1_WR_I,
    .send_ptr_addr = (uint32_t)RB_ADDR_IN1_RD_I,
    .meter_id = METER_IN1,
    .temp_data = 0,
    .inner_i = 0,
    .nibble_select = false};

// Ring buffer context variable for IN2.
ring_buf_item_t rb_in2 = {
    .write_ptr = 1,
    .send_ptr = 0,
    .write_ptr_addr = (uint32_t)RB_ADDR_IN2_WR_I,
    .send_ptr_addr = (uint32_t)RB_ADDR_IN2_RD_I,
    .meter_id = METER_IN2,
    .temp_data = 0,
    .inner_i = 0,
    .nibble_select = false};

// Ring buffer context variable for IN3.
ring_buf_item_t rb_in3 = {
    .write_ptr = 1,
    .send_ptr = 0,
    .write_ptr_addr = (uint32_t)RB_ADDR_IN3_WR_I,
    .send_ptr_addr = (uint32_t)RB_ADDR_IN3_RD_I,
    .meter_id = METER_IN3,
    .temp_data = 0,
    .inner_i = 0,
    .nibble_select = false};

// -------------------------------------------------------------------------------------------------

// DUMMY VARIABLE
uint8_t FRAM[256];
uint8_t bucket[64];

// DUMMY FUNCTION
void FRAM_read(uint32_t addr, uint8_t *buf, uint8_t len)
{
    if (len == 1)
    {
        *buf = FRAM[(uint8_t)addr];
        return;
    }

    for (uint8_t n = 0; n < len; n++)
    {
        buf[n] = FRAM[(uint8_t)addr + n];
    }
}

// DUMMY FUNCTION
void FRAM_write(uint32_t addr, uint8_t *data, uint8_t len)
{
    if (len == 1)
    {
        FRAM[(uint8_t)addr] = *data;
    }
    else
    {
        for (uint8_t n = 0; n < len; n++)
        {
            FRAM[(uint8_t)addr + n] = data[n];
        }
    }
}

// DUMMY FUNCTION
void getNow(uint8_t *buf)
{
    static uint8_t time = 0xD0;
    // get yy-mm-dd hh:mm:ss
    // buf[0] = 20;
    // buf[1] = 12;
    // buf[2] = 31;
    // buf[3] = 15;
    // buf[4] = 19;
    // buf[5] = 59;
    buf[0] = time;
    buf[1] = time;
    buf[2] = time;
    buf[3] = time;
    buf[4] = time;
    buf[5] = time;

    // quick thing to return changing values like
    time++;

    return;
}

// -------------------------------------------------------------------------------------------------

/**
 * Write data into the FRAM ring buffer.
 * @param [in] data: Some data of 4 bits.
 * @param [in|out] rbi: Ring buffer context variable.
 * @retval None
 *
 * Example Usage:
 * @code
 * ring_buf_item_t rb_in0 = {
 *     .write_ptr = 1,
 *     .send_ptr = 0,
 *     .write_ptr_addr = 0, // pick some fram address
 *     .send_ptr_addr = 1, // pick some other fram address
 *     .meter_id = 0, // pick  some number to identify a meter
 *     .temp_data = 0,
 *     .inner_i = 0,
 *     .nibble_select = false};
 * uint8_t temp;
 * for (uint8_t i = 1; i < 20; i++)
 * {
 *     temp = i % 16;
 *     FRAM_append_data(temp, &rb_in0);
 * }
 * @endcode
 */
void FRAM_append_data(uint8_t data, ring_buf_item_t *rbi)
{
    // Param FRAM address.
    uint32_t Pi;
    // Data FRAM address.
    uint32_t Di;

    // pick up where we left off
    FRAM_read(rbi->write_ptr_addr, &(rbi->write_ptr), 1);
    FRAM_read(rbi->send_ptr_addr, &(rbi->send_ptr), 1);

    // check if current block is full
    if (rbi->inner_i == RB_DATA_SIZE)
    {
        // ring buffer is full condition
        if ((rbi->write_ptr + 1) % RB_NUM_ITEMS != rbi->send_ptr)
        {
            // move to next ring buffer item
            rbi->write_ptr++;
            rbi->write_ptr %= RB_NUM_ITEMS;

            // store ring buffer index
            FRAM_write(rbi->write_ptr_addr, &(rbi->write_ptr), 1);

            // next block index starts from zero
            rbi->inner_i = 0;
            // and on upper nibble
            rbi->nibble_select = false;

            // debug
            // printf("- - - - - \n");
        } // if buffer full
        else
        {
            // TODO: return some error code
            // ...
            NOP();
            return;
        }
    } // if block full

    // get data start address
    Di = INDEX_TO_FRAM_DATA_ADDR(rbi->write_ptr % RB_NUM_ITEMS, rbi->meter_id);
    // get param start address
    Pi = INDEX_TO_FRAM_PARAM_ADDR(rbi->write_ptr % RB_NUM_ITEMS, rbi->meter_id);

    // write params into the fresh buffer (with only checking inner_i T0 gets written twice)
    if ((rbi->inner_i == 0) && rbi->nibble_select == false)
    {
        getNow(rbi->T0);

        // store T0
        // FRAM[Pi + ADDR_T0] = now()
        FRAM_write(Pi + RB_T0_YR, rbi->T0, 6);
    }

    // write in upper/lower nibble of temp_data in an alternating manner
    // store in FRAM when 2 x 4 bit of data is ready
    // NOTE: 4 bits of data might get lost on power loss, rbi->inner_i is not persistent
    if (rbi->nibble_select == false)
    {
        rbi->temp_data |= UPPER4BIT(data);
    }
    else
    {
        rbi->temp_data |= LOWER4BIT(data);

        // !!!
        FRAM_write(Di + rbi->inner_i, &(rbi->temp_data), 1);

        // store current write index
        FRAM_write(Pi + RB_INNER_PTR, &(rbi->inner_i), 1);

        rbi->inner_i++;

        // clear temp
        rbi->temp_data = 0;
    }
    rbi->nibble_select = !(rbi->nibble_select);
}

/**
 * Read ring buffer data from FRAM. Contains a timestamp and impulse counts.
 * See the README for more info, its easier to understand visually.
 * @param [out] buf - Data is written here.
 * @param [in|out] rbi: Ring buffer context variable.
 * @retval Number of bytes that was read, 0 if there is nothing.
 *
 * Example Usage:
 * @code
 * ring_buf_item_t rb_in0 = {
 *     .write_ptr = 1,
 *     .send_ptr = 0,
 *     .write_ptr_addr = 0, // pick some fram address
 *     .send_ptr_addr = 1, // pick some other fram address
 *     .meter_id = 0, // pick  some number to identify a meter
 *     .temp_data = 0,
 *     .inner_i = 0,
 *     .nibble_select = false};
 * uint8_t len;
 * uint8_t bucket[64];
 * len = FRAM_get_data(bucket, &rb_in0);
 * @endcode
 */
uint8_t FRAM_get_data(uint8_t *buf, ring_buf_item_t *rbi)
{
    // Param FRAM address.
    uint32_t Pi;
    // Data FRAM address.
    uint32_t Di;
    uint8_t temp_index;
    uint8_t length;

    // TODO: be kell varni hogy a kikuldes sikeres legyen, addig nem novelodhet a send_ptr!

    // pick up where we left off
    FRAM_read(rbi->write_ptr_addr, &(rbi->write_ptr), 1);
    FRAM_read(rbi->send_ptr_addr, &(rbi->send_ptr), 1);

    // temp (send) index points to where next send can happen
    temp_index = (rbi->send_ptr + 1) % RB_NUM_ITEMS;

    // condition to check if there is something to send
    if (temp_index != rbi->write_ptr)
    {
        // !!!
        // read how many bytes are written into the block
        Pi = INDEX_TO_FRAM_PARAM_ADDR(temp_index, rbi->meter_id);
        // Pi = INDEX_TO_FRAM_PARAM_ADDR(rbi.send_ptr);
        length = 0;
        FRAM_read(Pi + RB_INNER_PTR, &length, 1);
        // +1 to convert 'index' to 'number of elements'
        length += 1;

        // read T0
        FRAM_read(Pi + RB_T0_YR, buf, 6);

        // read measurement data
        Di = INDEX_TO_FRAM_DATA_ADDR(temp_index, rbi->meter_id);

        // buf pointer is incremented with size(T0)
        buf += 6;

        // NOTE: possible index out of bounds error here
        FRAM_read(Di, buf, length);

        return length + 6;
    }
    else
    {
        return 0;
    }
}

// -------------------------------------------------------------------------------------------------

void main()
{
    uint8_t temp;
    uint8_t len;

    // set initial values
    temp = 0;
    FRAM_write(RB_ADDR_IN0_RD_I, &temp, 1);
    FRAM_write(RB_ADDR_IN1_RD_I, &temp, 1);
    FRAM_write(RB_ADDR_IN2_RD_I, &temp, 1);
    FRAM_write(RB_ADDR_IN3_RD_I, &temp, 1);
    temp = 1;
    FRAM_write(RB_ADDR_IN0_WR_I, &temp, 1);
    FRAM_write(RB_ADDR_IN1_WR_I, &temp, 1);
    FRAM_write(RB_ADDR_IN2_WR_I, &temp, 1);
    FRAM_write(RB_ADDR_IN3_WR_I, &temp, 1);

    for (uint8_t i = 1; i < 20; i++)
    {
        temp = i % 16;
        // write smth
        FRAM_append_data(temp, &rb_in0);
        NOP();
        // read smth
        len = FRAM_get_data(bucket, &rb_in0);
        // mark a succesful read/send
        if (len > 0)
        {
            rb_in0.send_ptr++;
            rb_in0.send_ptr %= RB_NUM_ITEMS;
            FRAM_write(rb_in0.send_ptr_addr, &(rb_in0.send_ptr), 1);
            NOP();
        }

        // FRAM_append_data(temp, &rb_in1);
        // NOP();
        // FRAM_append_data(temp, &rb_in2);
        // NOP();
        // FRAM_append_data(temp, &rb_in3);
        // NOP();
    }

    /*
    // simple test
    {
        uint32_t addr = 10;
        // write 10 smth
        for (uint8_t i; i < 10; i++)
        {
            temp = 2 * i;
            FRAM_write((uint32_t)i, &temp, 1);
        }

        // read it out
        FRAM_read((uint32_t)0, bucket, 10);
        NOP();

    } // test
    */
}