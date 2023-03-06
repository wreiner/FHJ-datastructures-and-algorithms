#!/usr/bin/python

INPUT = [31, -41, 59, 26, -53, 58, 97, -93, -23, 84]

INPUT = [4, 3, -10, 3, -1, 2, 0, -3, 5, 7, -4, -8, -10, 4, 7, -30, -2, -6, 4, 7]

def brute_force():
    maxsum = 0

    for i in range(0, len(INPUT)):
        newsum = 0
        for j in range(i, len(INPUT)):
            newsum += INPUT[j]
            print(f"{i} to {j}: {newsum}")
            if newsum > maxsum:
                maxsum = newsum
    return maxsum

print(brute_force())
