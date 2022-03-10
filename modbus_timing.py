# The magic numbers are
# 3, [8], 13, 18, 23, 28, 33, 38, 43, 48, 53, 58

first_run = True


def something(n):
    global first_run

    if first_run:
        if (n == 8):
            first_run = False
        else:
            return 0

    return (n - 8) % 5 == 0


# --------------------------------------------------------------------------------------------------

# case 1
inputto = [2, 3, 8]
expected = [0, 0, 1]

# case 2
# inputto = [0, 1, 2, 3, 8, 13, 18, 23, 0, 1, 2, 3, 8]
# expected = [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1]

result = [int(something(i)) for i in inputto]

print("in: ", inputto)
print("out:", result)
print("correct?", result == expected)
