#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Brents Algorithm
    Hashmap Implementation

    Compile with:
        gcc -lm -ggdb -o brent brents_algorithm.c && ./brent
*/

#define HASHMAP_SIZE 100

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
    The hash function is a simple module function.
*/
int calculate_hash(int key, int modulo_value)
{
    return modulo_Euclidean(key, modulo_value);
}

/*
    Calculate the double hash value for a given key k with modulo m.
    The double hash function is h'(k) = 1 + k mod (m-2).
*/
int calculate_double_hash(int k, int m)
{
    return (1 + modulo_Euclidean(k, m - 2));
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

int brents_algorithm(int* hashmap, int i, int k, int m)
{
    fprintf(stdout, "-- BA for [k:%d] with [i:%d]\n", k, i);

    // end all
    if (*(hashmap + i) == -3) {
        return -1;
    }

    // position is already taken - probe for alternate position
    int ks = hashmap[i];
    fprintf(stdout, "pos [pos:%d] already taken by [ks:%d]\n", i, ks);

    int b = i - calculate_double_hash(k, m);
    if (b < 0) {
        b = calculate_hash(b, m);
    }

    // check if alternate position is empty
    if (*(hashmap + b) == -1) {
        // alternate position is empty - insert k
        fprintf(stdout, "will store [k:%d] to [pos:%d]\n", k, b);
        *(hashmap + b) = k;
        return b;
    }
    fprintf(stdout, "alternate pos [pos:%d] already taken by [kx:%d]\n", b, *(hashmap + b));

    // alternate position is not empty - try to relocate ks
    int bs = i - calculate_double_hash(ks, m);
    if (bs < 0) {
        bs = calculate_hash(bs, m);
    }
    if (*(hashmap + bs) == -1) {
        // alternate position is empty - move ks
        fprintf(stdout, "will move [ks:%d] from [old:%d] to [pos:%d]\n", ks, i, bs);
        *(hashmap + bs) = ks;
        // now original position is free - insert k
        fprintf(stdout, "will now store [k:%d] to [pos:%d]\n", k, i);
        *(hashmap + i) = k;
        return i;
    }
    fprintf(stdout, "cannot move [ks:%d] to [pos:%d], already taken by [kx:%d]\n", ks, bs, *(hashmap + bs));

    return brents_algorithm(hashmap, b, k, m);
}

int main()
{
    int hashmap[HASHMAP_SIZE];
    int basic_modulo_value = 7;
    int hashvalues[] = {12, 53, 5, 15, 2, 19, 7};
    int k = -1;
    int m = basic_modulo_value;

    // initialize the hashmap with -1 values
    memset(hashmap, -1, sizeof(hashmap));
    // set array stop
    hashmap[HASHMAP_SIZE - 1] = -3;

    for (int p = 0; p < sizeof(hashvalues)/sizeof(p); p++) {
        int k = hashvalues[p];

        // calculate first position
        int i = calculate_hash(k, m);

        fprintf(stdout, "POSPOS: (%d) mod %d = %d\n", k, m, i);

        // check if position is already taken in hashmap
        if (hashmap[i] == -1) {
            // not taken yet so we can insert k
            fprintf(stdout, "will store [k:%d] to [pos:%d]\n", k, i);

            hashmap[i] = k;
            continue;
        }

        // position is already taken - probe for alternate position
        if (brents_algorithm(hashmap, i, k, m) < 0) {
            fprintf(stdout, "cannot find empty position for [key:%d], exiting.\n", k);
            break;
        }
        // hashmap[position] = k;
    }

    fprintf(stdout, "-----\n");

    for (int i = 0; i < 100; i++) {
        if (hashmap[i] != -1) {
            fprintf(stdout, "[%d] = %d\n", i, hashmap[i]);
        }
    }

    fprintf(stdout, "-----\n");

    // int spos = -1;
    // int sval = -1;

    // sval = 7;
    // spos = search_key(hashmap, sval, m);
    // fprintf(stdout, "searching for [k:%d] ..\n", sval);
    // if (spos == -1) {
    //     fprintf(stdout, "[k:%d] not found..\n", sval);
    // } else {
    //     fprintf(stdout, "[k:%d] found on [pos:%d]..\n", sval, spos);
    // }

    // sval = 5;
    // spos = search_key(hashmap, sval, m);
    // fprintf(stdout, "searching for [k:%d] ..\n", sval);
    // if (spos == -1) {
    //     fprintf(stdout, "[k:%d] not found..\n", sval);
    // } else {
    //     fprintf(stdout, "[k:%d] found on [pos:%d]..\n", sval, spos);
    // }

    return 0;
}
