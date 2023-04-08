#include <stdio.h>
#include <string.h>

/*
    Linear Open Addressing
    Hashmap Implementation
*/

// The % operator in C is not the modulo operator but the remainder operator.
// https://stackoverflow.com/a/52529440
int modulo_Euclidean(int a, int b)
{
    int m = a % b;
    if (m < 0) {
        m = (b < 0) ? m - b : m + b;
    }
    return m;
}

int calculate_hash(int key, int modulo_value)
{
    return modulo_Euclidean(key, modulo_value);
}

int linear_open_addressing(int j, int k, int modulo_value)
{
    return j;
}

// Search for a key in the hashmap with a modulo of m.
// Return the position of element in the hashmap or -1 if not found.
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
        int s = linear_open_addressing(j, k, m);
        int nhash_pos = calculate_hash(pos - s, m);
        // fprintf(stdout, "LOA FOR %d HP (%d - %d) mod 7 = %d\n", k, pos, s, nhash_pos);

        if (*(hashmap + nhash_pos) == k) {
            return nhash_pos;
        }
    }
    return -1;
}

int main()
{
    int hashmap[100];
    int basic_modulo_value = 7;
    int hashvalues[] = {12, 53, 5, 15, 2, 19, 43, 7};
    int k = -1;
    int m = basic_modulo_value;

    memset(hashmap, -1, sizeof(hashmap));

    for (int i = 0; i < sizeof(hashvalues)/sizeof(k); i++) {
        int hash_pos = 0;
        int s = -1;
        int nhash_pos = -1;

        k = hashvalues[i];

        // calculate hash to get first possible position
        hash_pos = calculate_hash(k, m);
        // fprintf(stdout, "-----\n[%d] (%d) mod %d = %d\n", i, k, m, hash_pos);

        // position in hashmap is empty we can store key to hashmap
        if (hashmap[hash_pos] == -1) {
            fprintf(stdout, "will store [k:%d] to [pos:%d]\n", k, hash_pos);
            hashmap[hash_pos] = k;
            continue;
        } else {
            fprintf(stdout, "found [k:%d] on [pos:%d]\n", hashmap[hash_pos], hash_pos);
        }

        for (int j = 0; j <= m - 1; j++) {
            int s = linear_open_addressing(j, k, m);
            int nhash_pos = calculate_hash(hash_pos - s, m);
            fprintf(stdout, "LOA FOR %d HP (%d - %d) mod 7 = %d\n", k, hash_pos, s, nhash_pos);

            // subsequent position in hashmap is empty we can store key to hashmap
            if (hashmap[nhash_pos] == -1) {
                fprintf(stdout, "will store [k:%d] to [pos:%d]\n", k, nhash_pos);
                hashmap[nhash_pos] = hashvalues[i];
                break;
            } else {
                fprintf(stdout, "found [k:%d] on [pos:%d]\n", hashmap[nhash_pos], nhash_pos);
            }
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