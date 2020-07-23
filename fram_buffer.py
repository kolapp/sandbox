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
write_ptr = 1
send_ptr = 0

# fill with zeros, just for show
for x in range(RING_SIZE):
    FRAM[x % RING_SIZE] = 0

# semmi
elapsed = 0

# --- input ---
# T0 = datetime.now()
# T0 = datetime(2020, 2, 28, 23, 59)

# probabilites (0-100)
imp_prob = 100  # ez mindig 100
send_prob = 35

while True:
    try:
        # other
        time.sleep(1)
        elapsed += 1
        os.system('cls')
        # --- print items ---
        print(f"Time elapsed: {elapsed}\n")
        for k, v in FRAM.items():
            row = f'RAM{[k]} = {v}'
            print(
                # show write ptr
                'write->\t' if k == write_ptr else '\t',
                # show item and send ptr
                row + ' <- send' if k == send_ptr else row
            )
        print()
        print('- ' * 18)

        # --- ... ---
        # if send_ptr == write_ptr:
        # !!!
        if (write_ptr + 1) % RING_SIZE == send_ptr:
            send_prob = 50  # debug
            print('Buffer is full!')
            # continue

        # --- random incoming impulse ---
        if randint(0, 100) < imp_prob:
            # !!!
            if (write_ptr + 1) % RING_SIZE != send_ptr:
                # print(f'Incoming imp #{write_ptr}')
                FRAM[write_ptr % RING_SIZE] = '{:X}'.format(
                    randint(4096, 65535))
                write_ptr += 1
                write_ptr %= RING_SIZE

        # BUG: hulyeseget csinal, indulaskor kikuldi a 0-t is!!!
        # --- random outgoing packet ---
        if (randint(0, 100) < send_prob):
            # !!!
            if (send_ptr + 1) % RING_SIZE != write_ptr:
                print(f'Sending RAM[{send_ptr}]={FRAM[send_ptr]}')

                # mark sent item
                # FRAM[send_ptr % RING_SIZE] = '(' + str(FRAM[send_ptr % RING_SIZE]) + ')'
                p = send_ptr % RING_SIZE
                FRAM[p] = f'{FRAM[p]}(sent)'

                send_ptr += 1
                send_ptr %= RING_SIZE
            else:
                print('Sending nothing')

        # --- info
        print(f'write ptr: {write_ptr}')
        print(f'send  ptr: {send_ptr}')

    except KeyboardInterrupt:
        print('Bye')
        break
    except KeyError:
        send_ptr = 0
    except Exception as e:
        raise
