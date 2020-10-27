
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


def decompress_imp_msg_payload(p):
    """ Decompress water meter payload.

    Example:

    in:
        s = '140809091b8F000456'
             14 08 09 09 1b 8F 00 04 56
        that means:
        T0 = 14 08 09 09 1b (hex)
        mote state = 8F ...
        impulse data = 00 04 56 (hex nibbles and zero pairs)
    out:
        generator object that loops like:
        ['14', '08', '09', '09', '1b', '8F', '00', '00', '00', '00', '56']
    """

    items = split_every_n(p, 2)

    # keep first few items as is
    for i in range(0, 6):
        yield items[i]

    # TODO: mote state byte
    # ...

    i = 6
    try:
        while i < len(items):
            if items[i] == '00':
                # skip this item
                i += 1

                # yield 00 n times
                # NOTE: number of zeros is in hex number system
                for _ in range(int(items[i], 16)):
                    yield '00'
                # skip this item too
                i += 1
            # keep non zero items unchanged
            else:
                yield items[i]
                i += 1
    except IndexError as e:
        pass

    return


inp = "140809091b8F00010705"
# inp = 14 08 09 09 1b 8F 00 01 07 05
# expected result:
# out = 14 08 09 09 1b 8F 00 07 05

# inp = "140809091b8F0809030405060203"
# inp = 14 08 09 09 1b 8F 08 09 03 04 05 06 02 03
# expected result:
# out = 14 08 09 09 1b 8F 08 09 03 04 05 06 02 03

# inp = "140809091b8F010003040003"
# inp = 14 08 09 09 1b 8F 01 00 03 04 00 03
# expected result:
# out = 14 08 09 09 1b 8F 01 00 00 00 04 00 00 00

# inp = '140809091b8F000456'
# ['14', '08', '09', '09', '1b', '8F', '00', '00', '00', '00', '56']

print("inp:")
print(split_every_n(inp, 2))

print()
print("out:")
print(
    list(decompress_imp_msg_payload(inp))
)
print(
    ''.join(list(decompress_imp_msg_payload(inp)))
)
