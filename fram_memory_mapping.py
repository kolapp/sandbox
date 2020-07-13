from random import randint

PARAM_SIZE = 3
DATA_SIZE = 5
RING_SIZE = 4
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
print(
    '-' * 30
)
for n in range(STEP * RING_SIZE):
    FRAM[n] = '[]'


# ...
def index_to_mem_addr(ind):
    return (ind % RING_SIZE) * STEP + PARAM_SIZE


def append_to_fram(data):
    global ring_buf_i
    global inner_i
    global FRAM
    # check if full
    if inner_i == DATA_SIZE:
        # move to next ring buffer item
        ring_buf_i += 1
        # index buffer data from zero
        inner_i = 0
        # print()

    # data start index
    Ai = index_to_mem_addr(ring_buf_i)

    # write data
    FRAM[Ai + inner_i] = data
    # store current write index, kokany
    Pi = Ai - PARAM_SIZE

    # fill param space with empty data, just for show
    for n in range(0, PARAM_SIZE):
        FRAM[Pi + n] = 'p'
    FRAM[Pi] = f'w={Ai}+{inner_i}'

    # debug
    # print(
    #     Ai + inner_i,
    #     end=' '
    # )

    inner_i += 1


for abc in range(50):
    append_to_fram(1000 + abc)

    key = [x for x in FRAM.keys()]
    key.sort()

    for k in key:
        print(f'{k}: {FRAM[k]} ri={ring_buf_i}')
    print()
    print('-' * 30)
