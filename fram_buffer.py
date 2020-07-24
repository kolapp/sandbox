"""Test code for LoRa data saving/sending consumer/producer algorithm.
"""

from datetime import datetime, timedelta
from pprint import pprint
from random import randint
import time
import os


# init
RING_SIZE = 8
FRAM = {}
# start conditions
write_ptr = 1
send_ptr = 0

# log what happened, just for show
WRITE_LOG = []
SEND_LOG = []

# fill with zeros, just for show
for x in range(RING_SIZE):
    FRAM[x % RING_SIZE] = 0

# measure time, just for show
elapsed = 0

# probabilites (0-100)
imp_prob = 100  # ez mindig 100
send_prob = 75

while True:
    try:
        # just for show
        # time.sleep(2)
        elapsed += 1
        os.system('cls')

        # --- print items ---
        print(f"Time elapsed: {elapsed}\n")
        print(f'written:\t{WRITE_LOG}')
        print(f'sent:\t\t{SEND_LOG}')
        print('- ' * 20)
        print()

        for k, v in FRAM.items():
            row = f'RAM{[k]} = {v}'
            print(
                # show write ptr
                'write->\t' if k == write_ptr else '\t',
                # show item and send ptr
                row + ' <- send' if k == send_ptr else row
            )
        print()
        print('- ' * 20)

        # check if buffer is full, just for show
        if (write_ptr + 1) % RING_SIZE == send_ptr:
            print('Buffer is full!')
            # continue

        # --- random incoming impulse ---
        if randint(0, 100) < imp_prob:
            # !!!
            # condition to check if buffer is full
            if (write_ptr + 1) % RING_SIZE != send_ptr:
                # !!!
                # write random data into FRAM
                data = '{:X}'.format(randint(4096, 65535))
                FRAM[write_ptr % RING_SIZE] = data

                # just for show
                print(f'Writing RAM[{write_ptr}]={FRAM[write_ptr]}')
                WRITE_LOG.append(FRAM[write_ptr % RING_SIZE])

                # !!!
                # write pointer points to where next write will happen
                write_ptr += 1
                write_ptr %= RING_SIZE
        else:
            print('Writing nothing.')

        # --- random outgoing packet ---
        if (randint(0, 100) < send_prob):
            # !!!
            # condition to check if there is something to send
            if (send_ptr + 1) % RING_SIZE != write_ptr:
                # !!!
                # send pointer points to where next send will happen
                send_ptr += 1
                send_ptr %= RING_SIZE

                # !!!
                print(f'Sending RAM[{send_ptr}]={FRAM[send_ptr]}')

                # just for show
                SEND_LOG.append(FRAM[send_ptr])
                # mark sent item
                FRAM[send_ptr] = f'{FRAM[send_ptr]}(sent)'

        else:
            print('Sending nothing.')

        # --- info
        # print(f'write ptr: {write_ptr}')
        # print(f'send  ptr: {send_ptr}')

    except KeyboardInterrupt:
        print('Bye')
        break
    except KeyError:
        send_ptr = 0
    except Exception as e:
        raise
