#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Insertionsort

    Compile with:
        gcc -lm -ggdb -o inssort insertionsort.c && ./inssort
*/

/*
*/

int main()
{
    int unsorted[] = {15, 2, 43, 17, 4, 8, 47};
    // int unsorted[] = {7, 5, 2, 9, 4};
    int min_pos = 1;
    int remember = 0;
    int c = 0;
    int b = 0;

    // start with second element because first element is considered sorted
    for (int i = min_pos; i < sizeof(unsorted)/sizeof(min_pos); i++) {
        remember = unsorted[i];
        c = i;
        b = i-1;
        while (b >= 0) {
            if (remember < unsorted[b]) {
                unsorted[c] = unsorted[b];
                unsorted[b] = remember;
            }
            b--;
            c--;
        }
    }


    fprintf(stdout, "-----\n");

    for (int i = 0; i < sizeof(unsorted)/sizeof(min_pos); i++) {
        if (unsorted[i] != -1) {
            fprintf(stdout, "[%d] = %d\n", i, unsorted[i]);
        }
    }

    return 0;
}