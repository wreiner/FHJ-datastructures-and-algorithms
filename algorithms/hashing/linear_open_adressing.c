#include <stdio.h>

// The % operator in C is not the modulo operator but the remainder operator.
// https://stackoverflow.com/a/52529440
int modulo_Euclidean(int a, int b)
{
    int m = a % b;
    if (m < 0) {
        // m += (b < 0) ? -b : b; // avoid this form: it is UB when b == INT_MIN
        m = (b < 0) ? m - b : m + b;
    }
    return m;
}

int calculate_hash(int key, int modulo_value)
{
    return (modulo_Euclidean(key, modulo_value));
}

int linear_open_addressing(j, k, modulo_value)
{
    return j;
}

int main()
{
    int hashmap[100];
    int basic_modulo_value = 7;
    int hashvalues[7] = {12, 53, 5, 15, 2, 19, 43};
    int k = -1;
    int m = basic_modulo_value;

    // fprintf(stdout, "-----\n");
    // for (int aa = 10; aa >= -10; aa--) {
    //     fprintf(stderr, "%d = %d\n", aa, modulo_Euclidean(aa, 7));
    // }
    // fprintf(stdout, "-----\n");
    // return 0;

    memset(hashmap, -1, sizeof(hashmap));

    for (int i = 0; i < 8; i++) {
        int hash_pos = 0;
        int s = -1;
        int nhash_pos = -1;

        k = hashvalues[i];

        // calculate hash to get first possible position
        hash_pos = calculate_hash(k, m);
        fprintf(stdout, "-----\n(%d) mod %d = %d\n", k, m, hash_pos);

        // position in hashmap is empty we can store it to hashmap
        if (hashmap[hash_pos] == -1) {
            fprintf(stdout, "will store [k:%d] to [pos:%d]\n", k, hash_pos);
            hashmap[hash_pos] = k;
            continue;
        } else {
            fprintf(stdout, "found [k:%d] on [pos:%d]\n", hashmap[hash_pos], hash_pos);
        }

        for (int j = 0; j < m - 1; j++) {
            int s = linear_open_addressing(j, k, m);
            int nhash_pos = calculate_hash(hash_pos - s, m);
            fprintf(stdout, "LOA FOR %d HP (%d - %d) mod 7 = %d\n", k, hash_pos, s, nhash_pos);

            // fprintf(stdout, "LOA FOR %d HP %d %d\n", k, hash_pos, hashmap[hash_pos]);
            if (hashmap[nhash_pos] == -1) {
                fprintf(stdout, "will store [k:%d] to [pos:%d]\n", k, nhash_pos);
                hashmap[nhash_pos] = hashvalues[i];
                break;
            } else {
                fprintf(stdout, "found [k:%d] on [pos:%d]\n", hashmap[nhash_pos], nhash_pos);
            }
        }
    }

    for (int i = 0; i < 100; i++) {
        if (hashmap[i] != -1) {
            fprintf(stdout, "[%d] = %d\n", i, hashmap[i]);
        }
    }

    return 0;
}