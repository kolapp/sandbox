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

    try:

        dd = [int(tt, 16) for tt in split_every_n(s[0:2 * 6], 2)]
        T0 = datetime(
            year=dd[0] + 2000,  # rtc counts years from 2000
            month=dd[1],
            day=dd[2],
            hour=(dd[3] - 1) % 24,  # timezone something
            minute=dd[4],
            second=dd[5],
        )

        # convert every character/nibble from hex to int
        data = [int(d, 16) for d in list(s[2 * 6:])]

        for i, v in enumerate(data):
            # zero values dont matter
            if v != 0:
                yield (
                    T0 + timedelta(minutes=i),
                    v
                )
    except ValueError:
        print('szar: ', s)
        raise
        return


# test
for s in payload:
    parsed = parse(s)

    print(s)

    for p in parse(s):
        print(
            p[0], p[1]
        )

    print()

    # print(
    #     f'in: {s}'
    # )
