from datetime import datetime, timedelta
from pprint import pprint
from random import randint
import time
import os

# init
SIZE = 10
FRAM = {}
for x in range(SIZE):
    FRAM[x % SIZE] = 0
write_ptr = 1
send_ptr = 0
elapsed = 0

# --- input ---
# T0 = datetime.now()
T0 = datetime(2020, 2, 28, 23, 59)

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
                '>' if k == write_ptr else '',
                # show item and send ptr
                row + ' <- send' if k == send_ptr else row
            )
        print()
        print('- ' * 12)

        # --- other
        # if send_ptr == write_ptr:
        # !!!
        if (write_ptr + 1) % SIZE == send_ptr:
            send_prob = 50  # debug
            print('Buffer is full!')
            # continue

        # --- random incoming impulse ---
        if randint(0, 100) < imp_prob:
            # !!!
            if (write_ptr + 1) % SIZE != send_ptr:
                # print(f'Incoming imp #{write_ptr}')
                FRAM[write_ptr % SIZE] = randint(0, 60)
                write_ptr += 1
                write_ptr %= SIZE

        # --- random outgoing packet ---
        if (randint(0, 100) < send_prob):
            # !!!
            if (send_ptr + 1) % SIZE != write_ptr:
                print(f'Sending RAM[{send_ptr}]={FRAM[send_ptr]}')

                # mark sent item
                # FRAM[send_ptr % SIZE] = '(' + str(FRAM[send_ptr % SIZE]) + ')'
                FRAM[send_ptr % SIZE] = '-'

                send_ptr += 1
                send_ptr %= SIZE
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
