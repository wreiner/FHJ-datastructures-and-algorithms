#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Quadratic Open Addressing
    Hashmap Implementation

    Compile with:
        gcc -lm -ggdb -o quadoa quadratic_open_adressing.c && ./quadoa
*/

/*
    Round float to integer with < 0.5 down and >= 0.5 up.
    Source: https://stackoverflow.com/a/52870700
*/
#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

/*
    Perform an Euclidean modulo operation.
    The % operator in C is not the modulo operator but the remainder operator.
    Source: https://stackoverflow.com/a/52529440
*/
int modulo_Euclidean(int k, int m)
{
    int euclidean_modulo = k % m;
    if (euclidean_modulo < 0) {
        euclidean_modulo = (m < 0) ? euclidean_modulo - m : euclidean_modulo + m;
    }
    return euclidean_modulo;
}

/*
    Calculate the hash value for a given key k with modulo m.
*/
int calculate_hash(int key, int modulo_value)
{
    return modulo_Euclidean(key, modulo_value);
}

/*
    Generate a new hashmap index based on j using a quadaratic algorithm.
    The result of the divison j/2 is rounded up on 0.5 before square happens.
*/
int quadratic_open_addressing(int j, int k, int modulo_value)
{
    // round 0.5 up ..
    int x = FLOAT_TO_INT((float)j/(float)2);

    // .. before square
    return (int) pow(x, 2)*(int) pow(-1, j);
}

/* Search for a key k in the hashmap with a modulo of m.
   Return position of element in the hashmap or -1 if not found.
*/
int search_key(int* hashmap, int k, int m)
{
    int pos = -1;
    pos = calculate_hash(k, m);

    // key found returning
    if (*(hashmap + pos) == k) {
        return pos;
    }

    // key not found - searching
    for (int j = 0; j < m - 1; j++) {
        int s = quadratic_open_addressing(j, k, m);
        int nhash_pos = calculate_hash(pos - s, m);
        // fprintf(stdout, "QOA FOR %d HP (%d - %d) mod 7 = %d\n", k, pos, s, nhash_pos);

        if (*(hashmap + nhash_pos) == k) {
            return nhash_pos;
        }
    }

    // search without success
    return -1;
}

int main()
{
    int hashmap[100];
    int basic_modulo_value = 7;
    int hashvalues[] = {12, 53, 5, 15, 2, 19};
    int k = -1;
    int m = basic_modulo_value;

    // initialize the hashmap with -1 values
    memset(hashmap, -1, sizeof(hashmap));

    for (int i = 0; i < sizeof(hashvalues)/sizeof(k); i++) {
        int hash_pos = 0;
        int s = -1;
        int nhash_pos = -1;

        k = hashvalues[i];

        // calculate hash to get first possible position
        hash_pos = calculate_hash(k, m);
        fprintf(stdout, "-----\n[%d] (%d) mod %d = %d\n", i, k, m, hash_pos);

        // position in hashmap is empty we can store it to hashmap
        if (hashmap[hash_pos] == -1) {
            fprintf(stdout, "will store [k:%d] to [pos:%d]\n", k, hash_pos);
            hashmap[hash_pos] = k;
            continue;
        } else {
            fprintf(stdout, "found [k:%d] on [pos:%d]\n", hashmap[hash_pos], hash_pos);
        }

        int found = 0;

        for (int j = 0; j <= m - 1; j++) {
            int s = quadratic_open_addressing(j, k, m);
            int nhash_pos = calculate_hash(hash_pos - s, m);
            // fprintf(stdout, "QOA FOR %d HP (%d - %d) mod 7 = %d\n", k, hash_pos, s, nhash_pos);

            // fprintf(stdout, "QOA FOR %d HP %d %d\n", k, hash_pos, hashmap[hash_pos]);

            // place to store key in hashmap found
            if (hashmap[nhash_pos] == -1) {
                fprintf(stdout, "will store [k:%d] to [pos:%d]\n", k, nhash_pos);
                hashmap[nhash_pos] = hashvalues[i];
                found = 1;
                break;
            } else {
                fprintf(stdout, "found [k:%d] on [pos:%d]\n", hashmap[nhash_pos], nhash_pos);
            }
        }

        if (found == 0) {
            fprintf(stdout, "no open position found for [k:%d], exiting.\n\n", k);
            return -1;
        }
    }

    fprintf(stdout, "-----\n");

    for (int i = 0; i < 100; i++) {
        if (hashmap[i] != -1) {
            fprintf(stdout, "[%d] = %d\n", i, hashmap[i]);
        }
    }

    fprintf(stdout, "-----\n");

    int spos = -1;
    int sval = -1;

    sval = 7;
    spos = search_key(hashmap, sval, m);
    fprintf(stdout, "searching for [k:%d] ..\n", sval);
    if (spos == -1) {
        fprintf(stdout, "[k:%d] not found..\n", sval);
    } else {
        fprintf(stdout, "[k:%d] found on [pos:%d]..\n", sval, spos);
    }

    sval = 5;
    spos = search_key(hashmap, sval, m);
    fprintf(stdout, "searching for [k:%d] ..\n", sval);
    if (spos == -1) {
        fprintf(stdout, "[k:%d] not found..\n", sval);
    } else {
        fprintf(stdout, "[k:%d] found on [pos:%d]..\n", sval, spos);
    }

    return 0;
}