# import random

# random meter readings
# v = [random.randint(0, 100) for _ in range(2)]
# dummy_readings = {
#     "a": max(v),
#     "b": min(v),  # b < a
# }


def reading(meter):
    # dict of dummy return values for real meters
    dummy_readings = {
        "a": 200,
        "b": 100,
    }

    result = 0

    # meter is virtual
    if meter["expr"] is not None:
        for m in meter["expr"]:
            # virtual reading = sum(weights * real readings)
            tmp = reading(meters[m["id"]]) * m["weight"]
            result += tmp
            # just for show
            # print(f'{m["weight"]:+}*{m["id"]}', end=" ")
        # print()

    # meter is real
    else:
        result = dummy_readings[meter["id"]]

    return result


# --------------------------------------------------------------------------------------------------


if __name__ == "__main__":

    # split consumption between two meters in a ratio
    p = 0.6
    q = 1 - p

    # simplified table of metering devices
    # logical relations look like this:
    # https://excalidraw.com/#json=5405931659591680,pN7XRE2m0T4fJavnTANTxw
    meters = {
        "a": {
            "id": "a",
            "expr": None
        },
        "b": {
            "id": "b",
            "expr": None
        },
        "c": {
            "id": "c",
            "expr": [
                {"weight": p, "id": "a"},
                {"weight": -p, "id": "b"},
            ]
        },
        "d": {
            "id": "d",
            "expr": [
                {"weight": q, "id": "a"},
                {"weight": -q, "id": "b"},
            ]
        },
        "e": {
            "id": "e",
            "expr": [
                {"weight": 0.5, "id": "d"},
            ]

        },
        "f": {
            "id": "f",
            "expr": [
                {"weight": 0.5, "id": "d"},
            ]
        },
    }

    for m in meters:
        result = reading(meters[m])
        print(f"{m} = {result}")
    pass
