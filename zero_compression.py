from random import randint
from tqdm import tqdm


# test examples
# inn = [0, 0, 0, 0, 0, 0, 0, 7, 5, 0, 0, 10, 0]
# out = [0, 7, 7, 5, 0, 2, 10, 0, 1]

# inn = [0, 7, 5]
# out = [0, 1, 7, 5]

# inn = [8, 9, 3, 4, 5, 6, 2, 3, 5, 6]
# out = [8, 9, 3, 4, 5, 6, 2, 3, 5, 6]

# inn = [1, 3, 0, 0, 4, 0, 0, 0]
# out = [1, 3, 0, 2, 4, 0, 3]

inn = [1, 0, 2, 0, 3, 0, 4, 0, 5, 0]
out = [1, 0, 1, 2, 0, 1, 3, 0, 1, 4, 0, 1, 5, 0, 1]


# NOTE: keves 0-nal nem tomorit, hanem hizlal
def compress(inn):
    cnt = 0

    for n in inn:
        # zero
        if n == 0:
            cnt += 1
        # non zero
        else:
            # was zero before: [... 0 N]
            if cnt == 0:
                yield n
            # was no zero before [... N]
            else:
                yield 0
                yield cnt
                yield n
                cnt = 0
    # last item was zero: [... 0]
    if cnt != 0:
        yield 0
        yield cnt
        cnt = 0


histo = {}

# --- PARAMETERS ---
howmany = range(300 * 1000)
# howmany = range(3)
# input_length = range(0, randint(8, 60))
input_length = range(60)

for _ in tqdm(howmany, ascii=True):
    inn = [randint(0, 255) for _ in input_length]

    # add some zeros
    # zero_prob = 66
    # zero_prob = randint(0, 100)
    zero_prob = randint(66, 100)
    inn = [x if randint(0, 100) > zero_prob else 0 for x in inn]

    out = list(compress(inn))

    # see results
    # print(
    #     f'in:\t{inn}',
    #     f'out:\t{out}',
    #     f'input size:\t{len(inn)}',
    #     'compression:\t{:.2f}'.format(len(out) / len(inn)),
    #     'size change:\t{0:+d}'.format(len(out) - len(inn)),
    #     f'zero prob:\t{zero_prob}'
    #     '\n',
    #     sep='\n'
    # )

    # compression stats
    try:
        # L = len(out) - len(inn) # size change
        L = '{:.3}'.format(len(out) / len(inn))  # compression ratio
        histo[L] += 1
    except KeyError:
        histo[L] = 1

print(histo)


# print(
#     list(compress(inn)),
#     list(compress(inn)) == out,
#     sep='\n'
# )
