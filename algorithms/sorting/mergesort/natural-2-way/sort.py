"""
Sort an array with the requested algorithm
"""

from array import array


def sort(a: array, l: int, r: int) -> None:
    """
    Sort a list with the requested sorting algorithm
    :param a: array of values to sort
    :param l: left boundary index - where to start sorting
    :param r: right boundary index - where to stop sorting
    :return: None
    """

    # Begin implementation
    left_begin = l
    left_end = -1
    right_begin = -1
    right_end = -1

    # print("\n------- sort begin ------")
    for i in range(l, r):
        need_merge = False
        if a[i] > a[i+1]:
            # i is bigger than i+1 --> they are not in order
            # print(f"NOT IN ORDER, {a[i]} > {a[i+1]}")

            # found end of left array, starting to look for end of right array
            if left_end == -1:
                # print(f"will end left with {i}")
                left_end = i
                right_begin = i + 1
            else:
                # found end of right half
                right_end = i
                need_merge = True
                # print(f"RIGHT {right_begin}-{right_end}")
        # else:
        #     # i smaller than i+1 --> they are in order
        #     # print(f"IN ORDER, {a[i]} > {a[i+1]}")
        #     # right_end = i + 1

        if need_merge:
            # print(f"would merge {left_begin}:{left_end} with {right_begin}:{right_end}")
            merge(a, left_begin, left_end, right_begin, right_end)
            # print(f"back from merge {a}")
            left_end = right_end
            right_begin = right_end + 1
            right_end = -1

    if left_end > 0 and right_end < 0:
        right_end = i +1
        # right_begin += 1
        # print(f"end would merge {left_begin}:{left_end} with {right_begin}:{right_end}")
        merge(a, left_begin, left_end, right_begin, right_end)
        # print(f"end back from merge {a}")

    # End implementation


# Add your auxiliary methods here
# Begin implementation

def merge(a, left_begin, left_end, right_begin, right_end):
    # left_len = len(laeft_half)
    # right_len = len(right_half)

    # print(f"--- will now merge: ")
    str = ""
    for i in range(left_begin, left_end+1):
        str += f"{a[i]}, "
    # print(str)
    # print("and")
    for i in range(right_begin, right_end+1):
        str += f"{a[i]}, "
    # print(str)
    # print(f"--- WNM cont ")

    left_len = left_end - left_begin +1
    right_len = right_end - right_begin +1

    merged = []

    l = 0
    r = 0
    while True:
        if a[left_begin + l] < a[right_begin + r]:
            # print(f"ADDLEFT {a[left_begin + l]} < {a[right_begin + r]}")
            merged.append(a[left_begin + l])
            l += 1
        else:
            # print(f"ADDRIGHT {a[left_begin + l]} > {a[right_begin + r]}")
            merged.append(a[right_begin + r])
            r += 1

        # print(f"merge step: {merged}")

        if l == left_len:
            # print("left extend")
            merged.extend(a[right_begin+r:right_end+1])
            break

        if r == right_len:
            # print("right extend")
            merged.extend(a[left_begin+l:left_end+1])
            break
        # if l == left_len:
        #     merged.extend(right_half[r:])
        #     break

        # if r == right_len:
        #     merged.extend(left_half[l:])
        #     break

    # print(f"final merged: {merged}")
    # print(f"will replace data in a")

    # print(f"{left_begin+1} {right_end+1}")
    # a[left_begin+1:right_end+1] = merged
    for i in range(0, len(merged)):
        # print(f"MI will replace {a[left_begin+i]} with {merged[i]}")
        a[left_begin+i] = merged[i]

    return merged

# End implementation
