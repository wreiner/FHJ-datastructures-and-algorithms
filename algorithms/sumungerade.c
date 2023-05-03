#include <stdio.h>
#include <stdlib.h>

/*
    Sum odd numbers

    Compile with:
        gcc -lm -ggdb -o ../../../bin/sumungerade sumungerade.c && ../../../bin/sumungerade
*/

int sumOdd(int number) {
    int sum = 0;
    for (int i = 0; i <= number; i++) {
        if (i % 2 != 0) {
            sum = sum + i;
        }
    }
    return sum;
}

int main()
{
    fprintf(stdout, "%d", sumOdd(13));
}
