from random import randint
from datetime import datetime


# memory partition parameters
PARAM_SIZE = 5
DATA_SIZE = 5
RING_SIZE = 3

# ring buf parameter address mapping, must be in [0, PARAM_SIZE)
ADDR_T0 = 2 % PARAM_SIZE
ADDR_WRITE_PTR = 3 % PARAM_SIZE

# ...
STEP = DATA_SIZE + PARAM_SIZE
FRAM = {}
ring_buf_i = 1
inner_i = 0


# semmi
print(
    f'PARAM_SIZE={PARAM_SIZE}',
    f'DATA_SIZE={DATA_SIZE}',
    f'RING_SIZE={RING_SIZE}',
)
# fill mem space with empty data, just for show
for n in range(STEP * RING_SIZE):
    FRAM[n] = '[]'


# ...
def index_to_mem_data_addr(ind):
    return (ind % RING_SIZE) * STEP + PARAM_SIZE


#  ...
def index_to_mem_param_addr(ind):
    return (ind % RING_SIZE) * STEP


# ...
def append_to_fram(data):
    global ring_buf_i
    global inner_i
    global FRAM

    # check if full
    if inner_i == DATA_SIZE:
        # move to next ring buffer item
        ring_buf_i += 1
        # next buffer index starts from zero
        inner_i = 0

    # get data start index
    Ai = index_to_mem_data_addr(ring_buf_i)
    # get param start index, kokany
    Pi = index_to_mem_param_addr(ring_buf_i)

    # write params into fresh buffer
    if inner_i == 0:
        # fill param space with empty data, just for show
        for n in range(0, PARAM_SIZE):
            FRAM[Pi + n] = 'p'
        # store T0
        FRAM[Pi + ADDR_T0] = str(datetime.now())

    # store current write index
    FRAM[Pi + ADDR_WRITE_PTR] = f'w={Ai}+{inner_i}'

    # write data
    FRAM[Ai + inner_i] = data

    # debug
    # print(
    #     Ai + inner_i,
    #     end=' '
    # )

    inner_i += 1


for abc in range(50):
    append_to_fram(1000 + abc)

    # just for show
    # key = [x for x in FRAM.keys()]
    # key.sort()
    # for k in key:
    #     print(f'{k}: {FRAM[k]} ri={ring_buf_i}')
    # print()
    # print('-' * 30)
