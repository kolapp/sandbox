from pprint import pprint
from datetime import datetime
from datetime import timedelta

payload = [
    '140809091b0012005600',
    # ---
    # '1408090a1f00000000F0',
    # '1408090a0f0000003000',
    # '1408090a070000000000',
    # '140809093b0000100000',
    # '14080909330000000000',
    # '140809092b0010010000',
    # '14080909230000000000',
    # '140809091b0003200000',
    # '14080909130000000000',
    # '140809090b0000000000',
    # '140809090b0012345678',
    # ----------------------
    # '1408070a1f0002000000',
    # '1408070a270000010000',
    # '1408070a2f0000000000',
    # '1408070a370000000000',
    # '1408070b030000000000',
    # '1408070b0b0000000001',
    # '1408070b130001000100',
    # '1408070b1b0000012001',
    # '1408070b230000000000',
    # '1408070b2b0000000000',
    # '1408070b330001000000',
    # '1408070b3b0000000000',
    # '1408070c070000000000',
    # '1408070c0f0000100001',
    # '1408070c170000010000',
    # '1408070c1f0001110000',
    # '1408070c270000000100',
    # '1408070c2f0011000000',
    # '1408070c370010000000',
    # '1408070d030000000000',
    # '1408070d0b0000001000',
    # '1408070d130000000000',
    # '1408070d1b0000000000',
    # '1408070d230000000000',
    # '1408070d2b0000000000',
    # '1408070d330000000001',
    # '1408070d3b0001000010',
    # '1408070e070000000000',
    # '1408070e0f0000000000',
    # '1408070e170000000000',
    # '1408070e1f0000010000',
    # '1408070e270000000000',
    # '1408070e2f0000001000',
    # '1408070e370000000000',
    # '1408070f0b0000000000',
    # '1408070f130000000000',
    # '1408070f1b0000100000',
    # '1408070f230010000000',
    # '1408070f2b0000001001',
    # '1408070f330000000000',
    # '1408070f3b0000000000',
    # '14080710070000000000',
    # '140807100f0000000000',
    # '14080710170000000000',
    # '140807101f0000000000',
    # '14080710270000000000',
    # '140807102f0000000000',
    # '14080710370000000000',
    # '14080711030000000000',
    # '140807110b0000000000',
    # '14080711130000000000',
    # '140807111b0000000000',
    # '14080711230000000000',
    # '140807112b0000000000',
    # '14080711330000000000',
    # '140807113b0000000000',
    # '14080712070000000000',
    # '140807120f0000000000',
    # '14080712170000000000',
    # '140807121f0000000000',
    # '14080712270000000000',
    # '140807122f0000000000',
    # '14080712370000000000',
    # '14080713030000000000',
    # '140807130b0000000000',
    # '14080713130000000000',
    # '140807131b0000000000',
    # '14080713230000000000',
    # '140807132b0000000000',
    # '14080713330000000000',
    # '140807133b0000000000',
    # '14080714070000000000',
    # '140807140f0000000000',
    # '14080714170000000000',
    # '140807141f0000000000',
    # '14080714270000000000',
    # '140807142f0000000000',
    # '14080714370000000000',
    # '14080715030000000000',
    # '140807150b0000000000',
    # '14080715130000000000',
    # '140807151b0000000000',
    # '14080715230000000000',
    # '140807152b0000000000',
    # '14080715330000000000',
    # '140807153b0000000000',
    # '14080716070000000000',
    # '140807160f0000000000',
    # '14080716170000000000',
    # '140807161f0000000000',
    # '14080716270000000000',
    # '140807162f0000000000',
    # '14080716370000000000',
    # '14080717030000000000',
    # '140807170b0000000000',
    # '14080717130000000000',
    # '140807171b0000000000',
    # '14080717230000000000',
    # '140807172b0000000000',
    # '14080717330000000000',
    # '140807173b0000000000',
    # '14080800070000000000',
    # '140808000f0000000000',
    # '14080800170000000000',
    # '140808001f0000000000',
    # '14080800270000000000',
    # '140808002f0000000000',
    # '14080800370000000000',
    # '14080801030000000000',
    # '140808010b0000000000',
    # '14080801130000000000',
    # '140808011b0000000000',
    # '140808012b0000000000',
    # '14080801330000000000',
    # '140808013b0000000000',
    # '14080802070000000000',
    # '140808020f0000000000',
    # '14080802170000000000',
    # '140808021f0000000000',
    # '14080802270000000000',
    # '140808022f0000000000',
    # '14080802370000000000',
    # '14080803030000000000',
    # '140808030b0000000000',
    # '14080803130000000000',
    # '140808031b0000000000',
    # '14080803230000000000',
    # '140808032b0000000000',
    # '14080803330000000000',
    # '140808033b0000000000',
    # '14080804070000000000',
    # '140808040f0000000000',
    # '14080804170000000000',
    # '140808041f0000000000',
    # '14080804270000000000',
    # '140808042f0000000000',
    # '14080804370000000000',
    # '14080805030000000000',
    # '140808050b0000000000',
    # '14080805130000000000',
    # '140808051b0000000000',
    # '14080805230000000000',
    # '140808052b0000000000',
    # '14080805330000000000',
    # '140808053b0000000000',
    # '14080806070000000000',
    # '140808060f0000000000',
    # '14080806170000000000',
    # '140808061f0000000000',
    # '14080806270000000000',
    # '140808062f0000000000',
    # '14080806370000000000',
    # '14080807030000000000',
    # '140808070b0000000000',
    # '14080807130000000000',
    # '140808071b0000000000',
    # '14080807230010000000',
    # '140808072b0000000000',
    # '14080807330000000000',
    # '140808073b0000000000',
    # '14080808070000000000',
    # '140808080f0000000000',
    # '14080808170000000000',
    # '140808081f0000000000',
    # '14080808270000000000',
    # '140808082f0000000000',
    # '14080808370000000000',
    # '14080809030000000000',
    # '140808090b0000000000',
    # '14080809130000000000',
    # '140808091b0000000000',
    # '14080809230000000000',
    # '140808092b0000000000',
    # '14080809330000000000',
    # '140808093b0000001000',
    # '1408080a070000000000',
    # '1408080a0f0000000000',
    # '1408080a170000000000',
    # '1408080a1f0000000000',
    # '1408080a270000102112',
    # '1408080a2f0001000000',
    # '1408080a370000000000',
    # '1408080b030000000000',
    # '1408080b0b0000000000',
    # '1408080b130000000000',
    # '1408080b1b0010010000',
    # '1408080b230000000000',
    # '1408080b2b0000000000',
    # '1408080b330000000000',
    # '1408080b3b0000000000',
    # '1408080c070010000000',
    # '1408080c0f0000000000',
    # '1408080c170000000000',
    # '1408080c1f0000000000',
    # '1408080c270000000100',
    # '1408080c2f0000000000',
    # '1408080c370000000100',
    # '1408080d030000000100',
    # '1408080d0b0000010000',
    # '1408080d130000000000',
    # '1408080d1b0000000000',
    # '1408080d230000000000',
    # '1408080d2b0021010000',
    # '1408080d330000110210',
    # '1408080d3b0000000002',
    # '1408080e070000000000',
    # '1408080e0f0000000000',
    # '1408080e170000000000',
    # '1408080e1f0001000000',
    # '1408080e270000000000',
    # '1408080e2f0000000000',
    # '1408080e370001000000',
    # '1408080f030000000000',
    # '1408080f0b0000000000',
    # '1408080f130000000000',
    # '1408080f1b0000000000',
    # '1408080f230000000000',
    # '1408080f2b0000000000',
    # '1408080f330000000000',
    # '1408080f3b0000000000',
    # '14080810070000000000',
    # '140808100f0000000000',
    # '14080810170000000000',
    # '140808101f0000000000',
    # '14080810270000000000',
    # '140808102f0000000000',
    # '14080810370000000000',
    # '14080811030000000000',
    # '140808110b0000000000',
    # '14080811130000000000',
    # '140808111b0000000000',
    # '14080811230000000000',
    # '140808112b0000000000',
    # '14080811330000000000',
    # '140808113b0000000000',
    # '14080812070000000000',
    # '140808120f0000000000',
    # '14080812170000000000',
    # '140808121f0000000000',
    # '14080812270000000000',
    # '140808122f0000000000',
    # '14080812370000000000',
    # '14080813030000000000',
    # '140808130b0000000000',
    # '14080813130000000000',
    # '140808131b0000000000',
    # '14080813230000000000',
    # '140808132b0000000000',
    # '14080813330000000000',
    # '140808133b0000000000',
    # '14080814070000000000',
    # '140808140f0000000000',
    # '14080814170000000000',
    # '140808141f0000000000',
    # '14080814270000000000',
    # '140808142f0000000000',
    # '14080814370000000000',
    # '14080815030000000000',
    # '140808150b0000000000',
    # '14080815130000000000',
    # '140808151b0000000000',
    # '14080815230000000000',
    # '140808152b0000000000',
    # '14080815330000000000',
    # '140808153b0000000000',
    # '14080816070000000000',
    # '140808160f0000000000',
    # '14080816170000000000',
    # '140808161f0000000000',
    # '14080816270000000000',
    # '14080816370000000000',
    # '14080817030000000000',
    # '140808170b0000000000',
    # '14080817130000000000',
    # '140808171b0000000000',
    # '14080817230000000000',
    # '140808172b0000000000',
    # '14080817330000000000',
    # '140808173b0000000000',
    # '14080900070000000000',
    # '140809000f0000000000',
    # '14080900170000000000',
    # '140809001f0000000000',
    # '14080900270000000000',
    # '140809002f0000000000',
    # '14080900370000000000',
    # '14080901030000000000',
    # '140809010b0000000000',
    # '14080901130000000000',
    # '140809011b0000000000',
    # '14080901230000000000',
    # '140809012b0000000000',
    # '14080901330000000000',
    # '140809013b0000000000',
    # '14080902070000000000',
    # '140809020f0000000000',
    # '14080902170000000000',
    # '140809021f0000000000',
    # '14080902270000000000',
    # '140809022f0000000000',
    # '14080902370000000000',
    # '14080903030000000000',
    # '140809030b0000000000',
    # '14080903130000000000',
    # '140809031b0000000000',
    # '14080903230000000000',
    # '140809032b0000000000',
    # '14080903330000000000',
    # '140809033b0000000000',
    # '14080904070000000000',
    # '140809040f0000000000',
    # '14080904170000000000',
    # '140809041f0000000000',
    # '14080904270000000000',
    # '140809042f0000000000',
    # '14080904370000000000',
    # '14080905030000000000',
    # '140809050b0000000000',
    # '14080905130000000000',
    # '140809051b0000000000',
    # '14080905230000000000',
    # '140809052b0000000000',
    # '14080905330000000000',
    # '140809053b0000000000',
    # '14080906070000000000',
    # '140809060f0000000000',
    # '14080906170000000000',
    # '140809061f0000000000',
    # '14080906270000000000',
    # '140809062f0000000000',
    # '14080906370000000000',
    # '14080907030000000000',
    # '140809070b0000000010',
    # '14080907130000000000',
    # '140809071b0000000000',
    # '14080907230000000000',
    # '140809072b0000000000',
    # '14080907330000000000',
    # '140809073b0000000000',
    # '14080908070000000000',
    # '140809080f0000000000',
    # '14080908170000000000',
    # '140809081f0000000000',
    # '14080908270000000000',
    # '140809082f0000000000',
    # '14080908370000100000',
    # '14080909030000000000',
    # '140809090b0000000000',
    # '14080909130000000000',
    # '140809091b0000000000',
    # '14080909230000000000',
    # '140809092b0000000000',
    # '14080909330000000000',
    # '140809093b0000000000',
    # '1408090a070000000000',
    # '1408090a0f0000000000',
    # '1408090a1f0000000000',
    # '1408090a270000000000',
    # '1408090a2f0000000000',
    # '1408090a370000000000',
    # '1408090b030000000000',
    # '1408090b0b0000000000',
    # '1408090b130000000001',
    # '1408090b1b0000000000',
    # '1408090b230000000000',
    # '1408090b2b0000000000',
    # '1408090b330000000000',
    # '1408090b3b0000000000',
    # '1408090c070000000000',
    # '1408090c0f0000000000',
    # '1408090c170000000000',
    # '1408090c1f0000000000',
    # '1408090c270000000000',
    # '1408090c2f0000000000',
    # '1408090c370000000000',
    # '1408090d030000000000',
    # '1408090d0b0000000000',
    # '1408090d130010000000',
    # '1408090d1b0000000000',
    # '1408090d230000000000',
    # '1408090d2b0000000000',
    # '1408090d330000000000',
    # '1408090d3b0000000000',
    # '1408090e070000202121',
    # '1408090e170000000000',
    # '1408090e1f0000000000',
    # '1408090e270000000000',
    # '1408090e2f0000000000',
    # '1408090e370000000000',
    # '1408090f030000000000',
    # '1408090f0b0000000000',
    # '1408090f130000000000',
    # '1408090f1b0000000000',
    # '1408090f230000000000',
    # '1408090f2b0000000000',
    # '1408090f330000000000',
    # '1408090f3b0000000000',
    # '14080910070000000000',
    # '140809100f0000000000',
    # '14080910170000000000',
    # '140809101f0000000000',
    # '14080910270000000000',
    # '140809102f0000000000',
    # '14080910370000000000',
    # '14080911030000000000',
    # '140809110b0000000000',
    # '14080911130000000000',
    # '140809111b0000000000',
    # '14080911230000000000',
    # '140809112b0000000000',
    # '14080911330000000000',
    # '140809113b0000000000',
    # '14080912070000000000',
    # '140809120f0000000000',
    # '14080912170000000000',
    # '140809121f0000000000',
    # '14080912270000000000',
    # '140809122f0000000000',
    # '14080912370000000000',
    # '14080913030000000000',
    # '140809130b0000000000',
    # '14080913130000000000',
    # '140809131b0000000000',
    # '14080913230000000000',
    # '140809132b0000000000',
    # '14080913330000000000',
    # '140809133b0000000000',
    # '14080914070000000000',
    # '140809140f0000000000',
    # '14080914170000000000',
    # '140809141f0000000000',
    # '14080914270000000000',
    # '140809142f0000000000',
    # '14080914370000000000',
    # '14080915030000000000',
    # '140809150b0000000000',
    # '14080915130000000000',
    # '140809151b0000000000',
    # '14080915230000000000',
    # '140809152b0000000000',
    # '14080915330000000000',
    # '140809153b0000000000',
    # '14080916070000000000',
    # '140809160f0000000000',
    # '14080916170000000000',
    # '140809161f0000000000',
    # '14080916270000000000',
    # '140809162f0000000000',
    # '14080916370000000000',
    # '14080917030000000000',
    # '140809170b0000000000',
    # '14080917130000000000',
    # '140809171b0000000000',
    # '14080917230000000000',
    # '140809172b0000000000',
    # '14080917330000000000',
    # '140809173b0000000000',
    # '14080a00070000000000',
    # '14080a000f0000000000',
    # '14080a00170000000000',
    # '14080a001f0000000000',
    # '14080a00270000000000',
    # '14080a002f0000000000',
    # '14080a00370000000000',
    # '14080a01030000000000',
    # '14080a010b0000000000',
    # '14080a01130000000000',
    # '14080a011b0000000000',
    # '14080a01230000000000',
    # '14080a012b0000000000',
    # '14080a01330000000000',
    # '14080a02070000000000',
    # '14080a020f0000000000',
    # '14080a02170000000000',
    # '14080a021f0000000000',
    # '14080a02270000000000',
    # '14080a022f0000000000',
    # '14080a02370000000000',
    # '14080a03030000000000',
    # '14080a030b0000000000',
    # '14080a03130000000000',
    # '14080a031b0000000000',
    # '14080a03230000000000',
    # '14080a032b0000000000',
    # '14080a03330000000000',
    # '14080a033b0000000000',
    # '14080a04070000000000',
    # '14080a040f0000000000',
    # '14080a04170000000000',
    # '14080a041f0000000000',
    # '14080a04270000000000',
    # '14080a042f0000000000',
    # '14080a04370000000000',
    # '14080a05030000000000',
    # '14080a050b0000000000',
    # '14080a05130000000000',
    # '14080a051b0000000000',
    # '14080a05230000000000',
    # '14080a052b0000000000',
    # '14080a05330000000000',
    # '14080a053b0000000000',
    # '14080a06070000000000',
    # '14080a060f0000000000',
    # '14080a06170000000000',
    # '14080a061f0000000000',
    # '14080a06270000000000',
    # '14080a062f0000000000',
    # '14080a06370000000100',
    # '14080a07030000010010',
    # '14080a070b0000000000',
    # '14080a07130000000010',
    # '14080a071b0000000000',
    # '14080a07230010000000',
    # '14080a072b0010000000',
    # '14080a07330000010000',
    # '14080a073b0000000000',
    # '14080a08070000001000',
    # '14080a080f0000100001',
    # '14080a08170000000000',
    # '14080a081f0000000000',
    # '14080a08270000010000',
    # '14080a082f0001000000',
    # '14080a08370000000000',
    # '14080a09030000000000',
    # '14080a090b0010000000',
    # '14080a09130000000010',
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


def parse_payload(s):
    """ Convert nonsense payload

    Example:
    in:
        s = '140809091b0012005600'

        T0 = 14 08 09 09 1b 00 (hex)
        data = 12 00 56 00 (hex nibbles)
    out:
        generator object that loops tuples like this:
        (measurement time, impulse count)
        (2020-08-09 08:27:00, 1)
        (2020-08-09 08:28:00, 2)
        (2020-08-09 08:31:00, 5)
        (2020-08-09 08:32:00, 6)

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
    parsed = parse_payload(s)

    print(s)

    for p in parse_payload(s):
        print(
            p[0], p[1]
        )

    print()

    # print(
    #     f'in: {s}'
    # )