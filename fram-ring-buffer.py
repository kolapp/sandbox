import numpy
import schedule
import time
from random import randint

# ring buffer parameters
BUF_SIZE = 5
OFFSET_IN0 = 0
OFFSET_IN1 = OFFSET_IN0 + BUF_SIZE + 0

# ...
FRAM = {}
FRAM['write_ptr_in0'] = OFFSET_IN0
FRAM['write_ptr_in1'] = OFFSET_IN1
temp = ''
hi_lo = False  # write upper or lower 4 bit

print(
    'SIZE:', BUF_SIZE,
    'OFFSET_IN0:', OFFSET_IN0,
    'OFFSET_IN1:', OFFSET_IN1,
)


def task(**kwargs):
    global hi_lo
    global temp
    hi_lo = not hi_lo

    r = randint(0, 16)
    if hi_lo:
        temp = ''  # clear it
        temp = f'|{str(r)}'
    else:
        temp = f'{str(r)}{temp}'
        # we have 8 bytes of data, write it to fram
        wp = FRAM['write_ptr_in0']
        FRAM[wp] = temp
        FRAM['write_ptr_in0'] += 1

    # print(temp)
    print(FRAM)

    return


if __name__ == '__main__':
    schedule.every(2).seconds.do(task, offset=OFFSET_IN0)

    while True:
        try:
            schedule.run_pending()
            time.sleep(1)
        except KeyboardInterrupt:
            print('Bye')
            break
