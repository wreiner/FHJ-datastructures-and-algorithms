#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Bubblesort

    Compile with:
        gcc -lm -ggdb -o bubblesort bubblesort.c && ./bubblesort
*/

/*
*/

int main()
{
    int unsorted[] = {15, 2, 43, 17, 4, 8, 47};
    // int unsorted[] = {7, 5, 2, 9, 4};
    int remember = 0;
    int swap = 1;

    while (swap) {
        swap = 0;
        for (int i = 0; i < sizeof(unsorted)/sizeof(remember); i++) {
            if (i == sizeof(unsorted)/sizeof(remember) - 1) {
                break;
            }
            if (unsorted[i] > unsorted[i+1]) {
                remember = unsorted[i];
                unsorted[i] = unsorted[i+1];
                unsorted[i+1] = remember;
                swap = 1;
            }
        }
    }

    fprintf(stdout, "-----\n");

    for (int i = 0; i < sizeof(unsorted)/sizeof(remember); i++) {
        if (unsorted[i] != -1) {
            fprintf(stdout, "[%d] = %d\n", i, unsorted[i]);
        }
    }

    return 0;
}