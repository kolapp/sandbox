PARAM_SIZE = 10
DATA_SIZE = 3
RING_SIZE = 2
STEP = DATA_SIZE + PARAM_SIZE


def index_to_mem_addr(ind):
    return (ind % RING_SIZE) * STEP + PARAM_SIZE


i = 0
j = 0
for _ in range(0, 30):

    # check if full
    if j == DATA_SIZE:
        # move to next ring buffer item
        i += 1
        # index buffer data from zero
        j = 0
        print()

    # data start index
    Ai = index_to_mem_addr(i)

    print(
        Ai + j,
        end=' '
    )

    j += 1
