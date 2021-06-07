
def reading(meter):
    # dict of dummy return values for real meters
    dummy_readings = {
        "b": 100,
        "c": 80,
        "d": 5,
    }

    result = 0

    # meter is virtual
    if meter["expr"] is not None:
        for m in meter["expr"]:
            # virtual reading = sum(weights * real readings)
            tmp = reading(meters[m["id"]]) * m["weight"]
            result += tmp
            # just for show
            print(f'{m["weight"]:+}*{m["id"]}', end=" ")

    # meter is real
    else:
        result = dummy_readings[meter["id"]]

    return result


# --------------------------------------------------------------------------------------------------


if __name__ == "__main__":

    # simplified table of metering devices
    meters = {
        "a": {
            "id": "a",
            "expr": [
                {
                    "weight": 1,
                    "id": "b"
                },
                {
                    "weight": -0.5,
                    "id": "c"
                },
                {
                    "weight": -1,
                    "id": "d"
                }
            ]
        },
        "b": {
            "id": "b",
            "expr": None
        },
        "c": {
            "id": "c",
            "expr": None
        },
        "d": {
            "id": "d",
            "expr": None
        },
    }

    result = reading(meters["a"])
    pass
