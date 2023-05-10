#!/usr/bin/env python3

import unittest
from array import array
import sort
from random import randint
from time import perf_counter


perf_test = True
random_numbers = 5000


class SortTest(unittest.TestCase):

    def test_self(self):
        # a = array('i', [4, 3, 2, 7, 5, 6])
        a = array('i', [4, 3, 2, 7, 5, 6, 8, 9, 1])
        expected = array.tolist(a)
        sort.sort(a, 0, len(a) - 1)
        expected.sort()
        self.assertEqual(a.tolist(), expected)

    def test_ascending(self):
        a = array('i', [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
        expected = array.tolist(a)
        sort.sort(a, 0, len(a) - 1)
        expected.sort()
        self.assertEqual(a.tolist(), expected)

    def test_descending(self):
        a = array('i', [10, 9, 8, 7, 6, 5, 4, 3, 2, 1])
        expected = array.tolist(a)
        sort.sort(a, 0, len(a) - 1)
        expected.sort()
        self.assertEqual(a.tolist(), expected)

    def test_unsorted(self):
        a = array('i', [31, -41, 59, 26, -53, 58, 97, -93, -23, 84])
        expected = array.tolist(a)
        sort.sort(a, 0, len(a) - 1)
        expected.sort()
        self.assertEqual(a.tolist(), expected)

    def test_equal(self):
        a = array('i', [5, 5, 5, 3, 3, 7, 7, 1, 1, 1])
        expected = array.tolist(a)
        sort.sort(a, 0, len(a) - 1)
        expected.sort()
        self.assertEqual(a.tolist(), expected)

    def test_empty(self):
        a = array('i', [])
        expected = array.tolist(a)
        sort.sort(a, 0, len(a) - 1)
        expected.sort()
        self.assertEqual(a.tolist(), expected)

    def test_strings(self):
        a = [ "Haus", "Alm", "Zaun", "Hühner" ]
        expected = a.copy()
        sort.sort(a, 0, len(a) - 1)
        expected.sort()
        self.assertEqual(a, expected)

    @unittest.skipUnless(perf_test == True, "No performance tests configured")
    def test_random(self):
        a = array('i', [])
        for i in range(random_numbers):
            a.append(randint(-random_numbers, random_numbers))
        expected = array.tolist(a)
        start_time = perf_counter()
        sort.sort(a, 0, len(a) - 1)
        sort_time = perf_counter() - start_time
        start_time = perf_counter()
        expected.sort()
        ref_time = perf_counter() - start_time
        self.assertEqual(a.tolist(), expected)
        print(f"Time for sorting {random_numbers} numbers: {sort_time}, reference time: {ref_time}")


if __name__ == '__main__':
    unittest.main()
