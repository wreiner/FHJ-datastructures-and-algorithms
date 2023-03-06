#!/usr/bin/python

import os

INPUT = [31, -41, 59, 26, -53, 58, 97, -93, -23, 84]

INPUT = [4, 3, -10, 3, -1, 2, 0, -3, 5, 7, -4, -8, -10, 4, 7, -30, -2, -6, 4, 7]

def create_side_maxima(calculation_side, side_values):
    sum = 0
    max = 0

    print(f"create_side_maxima: {calculation_side}: {side_values}")

    # 0 = left, 1 = right
    if calculation_side == 0:
        for i in side_values:
            sum += i
            if (sum > max):
                max = sum
    else:
        for i in side_values[::-1]:
            sum += i
            if (sum > max):
                max = sum
    if max < 0:
        return 0
    return max

def divide_and_conquer(array_part):
    part_length = len(array_part)
    if part_length == 1:
        if array_part[0] > 1:
            return array_part[0]
        else:
            return 0

    divisor = part_length // 2
    left_half = divide_and_conquer(array_part[0:divisor])
    right_half = divide_and_conquer(array_part[divisor:])

    left_max = create_side_maxima(1, array_part[0:divisor])
    print(f"left_max: {left_max}")
    right_max = create_side_maxima(0, array_part[divisor:])
    print(f"right_max: {right_max}")
    lr_max_sum = left_max + right_max

    maxtsum = max(left_half, right_half, lr_max_sum)

    print(f"will return {maxtsum} of max({left_half}, {right_half}, {lr_max_sum} [{left_max}, {right_max}])")
    return maxtsum

os.system('clear')
print(divide_and_conquer(INPUT))
