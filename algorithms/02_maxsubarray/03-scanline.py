#!/usr/bin/python

import os

INPUT = [31, -41, 59, 26, -53, 58, 97, -93, -23, 84]

INPUT = [4, 3, -10, 3, -1, 2, 0, -3, 5, 7, -4, -8, -10, 4, 7, -30, -2, -6, 4, 7]

def scanline(data):
    scan_max = 0
    bis_max = 0

    for i in data:
        if scan_max + i > 0:
            scan_max = scan_max + i
        else:
            scan_max = 0

        print(f"{i}: SM: {scan_max} | BM: {bis_max}")

        bis_max = max(scan_max, bis_max)
    return bis_max

os.system('clear')
print(scanline(INPUT))
