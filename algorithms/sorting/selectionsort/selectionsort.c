#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Selectionsort

    Compile with:
        gcc -lm -ggdb -o selsort selectionsort.c && ./selsort
*/

/*
    Gegeben sind fünf Spielkarten [7][5][2][9][4] unsortiert in einer Reihe, die  der Größe nach aufsteigend nach dem MinSort-Prinzip geordnet werden sollen.
    Man sieht dabei im ersten Schritt erstmal alle Karten der Reihe nach an und sucht dann nach der Karte mit dem niedrigsten Wert – in diesem Fall die 2.
    Die 2 wird dann mit der ersten Stelle des unsortierten Bereichs, also der 7, vertauscht.
    Die Karte 2 ist damit auf ihrem richtigen Platz und gilt als fertigsortiert, deshalb wird sie im weiteren Verlauf nicht mehr beachtet.
    Nun zum zweiten Wert – der 5, welcher mit der 7, der 9 und der 4 verglichen wird. Die 4 ist kleiner als die 5 und wird deshalb wieder mit der 5 vertauscht. Der Vorgang wird mit der der Karte 7 wiederholt, die dann ihren Platz mit der 5 wechselt und zum Schluss werden auch noch die Karten 9 und 7 ausgetauscht. Am Ende erhält man den fertig sortierte Array: [2][4][5][7][9]
*/

int main()
{
    int unsorted[] = {7, 5, 2, 9, 4};
    int min = unsorted[0];
    int min_pos = 0;
    int unsorted_begin = 0;

    while (1) {
        if (unsorted_begin == sizeof(unsorted)/sizeof(min)) {
            break;
        }

        for (int i = min_pos; i < sizeof(unsorted)/sizeof(min); i++) {
            // find smallest value
            if (unsorted[i] < min) {
                min = unsorted[i];
                min_pos = i;
            }
        }

        unsorted[min_pos] = unsorted[unsorted_begin];
        unsorted[unsorted_begin] = min;
        unsorted_begin++;
        min = unsorted[unsorted_begin];
    }

    fprintf(stdout, "-----\n");

    for (int i = 0; i < sizeof(unsorted)/sizeof(min); i++) {
        if (unsorted[i] != -1) {
            fprintf(stdout, "[%d] = %d\n", i, unsorted[i]);
        }
    }

    return 0;
}