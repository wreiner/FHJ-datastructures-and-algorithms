#!/usr/bin/python

import os

# INPUT = [31, -41, 59, 26, -53, 58, 97, -93, -23, 84]

INPUT = [1,2,3,5,9,4,6,7,8,10]

# INPUT = [4, 3, -10, 3, -1, 2, 0, -3, 5, 7, -4, -8, -10, 4, 7, -30, -2, -6, 4, 7]

# INPUT = [31, 41, 26, 58]

def merge(left_half, right_half):
    left_len = len(left_half)
    right_len = len(right_half)

    merged = []

    l = 0
    r = 0
    while True:
        if left_half[l] < right_half[r]:
            merged.append(left_half[l])
            l += 1
        else:
            merged.append(right_half[r])
            r += 1

        if l == left_len:
            merged.extend(right_half[r:])
            break

        if r == right_len:
            merged.extend(left_half[l:])
            break

    return merged

def mergesort(array_part):
    part_length = len(array_part)

    print(f"mergesort called with {array_part} with {part_length} elements")

    if part_length == 1:
        return array_part

    divisor = part_length // 2
    left_half = mergesort(array_part[0:divisor])
    right_half = mergesort(array_part[divisor:])

    print(f"will merge LH: {left_half} | RH: {right_half}")

    merged = merge(left_half, right_half)
    print(f"new merged part: {merged}")

    return merged

os.system('clear')
print(mergesort(INPUT))
