#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Quicksort in-situ

    Compile with:
        gcc -lm -ggdb -o ../../../bin/quicksort quicksort.c && ../../../bin/quicksort
*/

int quicksort(int* unsorted, int l, int r)
{
    int i, j, v, t = 0;

    if (r < l) {
        return 0;
    }

    int pivot = unsorted[r];
    fprintf(stdout, "### \npivot %d at %d\n", pivot, r);

    i = l;
    j = r;
    int ri = l;
    int rj = r;

    while (1) {
        int remember = -1;
        int lower = -1;
        int bigger = -1;

        for (i = ri; i < r; i++) {
            fprintf(stdout, "i: %d\n", i);
            if (i >= rj) {
                break;
            }
            if (unsorted[i] > pivot) {
                bigger = unsorted[i];
                fprintf(stdout, "found bigger %d at %d\n", bigger , i);
                break;
            }
        }

        for (j = rj; j > l; j--) {
            fprintf(stdout, "j: %d\n", j);
            if (j < i) {
                break;
            }
            if (unsorted[j] < pivot) {
                lower = unsorted[j];
                fprintf(stdout, "found lower %d at %d\n", lower, j);
                break;
            }
        }

        if (lower < 0 || bigger < 0) {
            fprintf(stdout, "abort reached\n");
            fprintf(stdout, "%d > %d, will swap pivot %d and %d\n", unsorted[i], pivot, r, i);

            // swap pivot into right place
            remember = unsorted[i];
            unsorted[i] = unsorted[r];
            unsorted[r] = remember;
            break;
        }

        if (bigger > lower) {
            fprintf(stdout, "%d > %d, will swap places %d and %d\n", bigger, lower, i, j);

            // swap
            remember = unsorted[i];
            unsorted[i] = unsorted[j];
            unsorted[j] = remember;
        }

        fprintf(stdout, "-----\n");

        for (int k = l; k <= r; k++) {
            fprintf(stdout, "[%d] = %d\n", k, unsorted[k]);
        }

        ri = i;
        rj = j;
    }

    fprintf(stdout, "-------- FH %d-%d | SH %d-%d\n", l, i-1, i+1, r);
    quicksort(unsorted, l, i-1);
    quicksort(unsorted, i+1, r);

    return 0;
}

int main()
{
    int unsorted[] = {15, 2, 43, 17, 4, 8, 47};
    // int unsorted[] = {5, 7, 3, 1, 6, 4};
    // int unsorted[] = {7, 6, 2, 3, 1, 5, 4, 12, 9, 15, 10, 14, 13, 11, 8};
    // int unsorted[] = {7, 5, 2, 9, 4};
    int remember = 0;
    int swap = 1;

    quicksort(unsorted, 0, sizeof(unsorted)/sizeof(remember)-1);

    fprintf(stdout, "-----\n");

    for (int i = 0; i < sizeof(unsorted)/sizeof(remember); i++) {
        if (unsorted[i] != -1) {
            fprintf(stdout, "[%d] = %d\n", i, unsorted[i]);
        }
    }

    return 0;
}
