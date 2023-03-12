#!/usr/bin/env python3

import sys

class StackEmptyException(Exception):
    pass

class Stack:
    STACK_PADDING = 5

    def __init__(self) -> None:
        # initiate the stack with a size of 5 elements
        self._element_count = 0
        self._max_elements = 0

        self.__expand_stack__()

    def __expand_stack__(self):
        new_length = self._max_elements + self.STACK_PADDING
        print(f"will expand the stack to {new_length} elements ..")

        self.new_stack = [None] * new_length
        self.__transfer_elements_to_new_stack__()

        self._stack = self.new_stack
        self._max_elements = new_length

    def __transfer_elements_to_new_stack__(self):
        for i in range(0, self._max_elements):
            print(f"will move element [i: {self._stack[i]}] to new stack ..")
            self.new_stack[i] = self._stack[i]

    def spush(self, value):
        if self._element_count == self._max_elements:
            self.__expand_stack__()

        print(f"will add elemnt with value {value} to top of stack ..")
        self._stack[self._element_count] = value
        self._element_count += 1

        print(self._stack)

    def spop(self):
        if self._element_count == 0:
            print("error, stack is empty, cannot remove element.")
            raise StackEmptyException

        value = self._stack[self._element_count - 1] = None
        value = self._stack[self._element_count - 1]
        print(f"will remove element with value {value} from top of the stack ..")

        self._element_count -= 1

        print(self._stack)

        return value

    def traverse_stack(self):
        i = self._element_count
        while (i > 0):
            print(f"{i}: {self._stack[i-1]}")
            i -= 1

    def get_element_count(self):
        return self._element_count

class BraceCheck:
    def __init__(self):
        self._bracecheck = Stack()

    def check_brace_string(self, string_of_braces):
        for brace in string_of_braces:
            if brace == "(":
                self._bracecheck.spush(1)
            elif brace == ")":
                try:
                    self._bracecheck.spop()
                except StackEmptyException:
                    return False

        if self._bracecheck.get_element_count() > 0:
            return False

        return True


braci = BraceCheck()
if not braci.check_brace_string("(((()"):
    print("brace mismatch")
    sys.exit(1)

print("braces match")
