from pprint import pprint
from datetime import datetime
from datetime import timedelta

payload = [
    '1408090a1f00000000F0',
    '1408090a0f0000003000',
    '1408090a070000000000',
    '140809093b0000100000',
    '14080909330000000000',
    '140809092b0010010000',
    '14080909230000000000',
    '140809091b0003200000',
    '14080909130000000000',
    '140809090b0000000000',
    '140809090b0012345678',
]


def split_every_n(string, n):
    """ Split a string in every n-th character.
        Returns a list of n length string.

        Example:
        in:
            string = 'abcd'
            n = 2
        out:
            returns ['ab', 'cd']
    """
    return [string[i:i + n] for i in range(0, len(string), n)]


def parse(s):
    """ Convert nonsense payload

    Example:
    in:
        s = '140809091b0003200000'
        T0 = 14 08 09 09 1b 00 (hex)
        data = 03 20 00 00 (hex nibbles)
    out:
        T0 = 2020-08-09 08:27:00
        data = [0, 3, 2, 0, 0, 0, 0, 0]

    """

    # TODO: implement zero decompression
    # ...

    parsed = {'T0': 'n/a', 'data': 'n/a', 'sum': 0}

    try:

        T0 = [int(tt, 16) for tt in split_every_n(s[0:2 * 6], 2)]
        parsed['T0'] = datetime(
            year=T0[0] + 2000,  # rtc counts years from 2000
            month=T0[1],
            day=T0[2],
            hour=(T0[3] - 1) % 24,  # timezone something
            minute=T0[4],
            second=T0[5],
        )

        # convert every character/nibble from hex to int
        data = [int(d, 16) for d in list(s[2 * 6:])]
        parsed['data'] = data

        # sum it for fun
        parsed['sum'] = sum(data)

        return parsed
    except ValueError:
        print('szar: ', s)
        return parsed


# test
for s in payload:
    parsed = parse(s)

    print()

    print(
        parsed['T0'],
        parsed['data'],
        # parsed['sum'],
        #     # '\n',
        #     # '- ' * 25,
        #     # '\n',
    )

    for i, v in enumerate(parsed['data']):
        if v != 0:
            print(
                parsed['T0'] + timedelta(minutes=i),
                ':',
                v,
            )
