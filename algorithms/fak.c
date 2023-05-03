#include <stdio.h>
#include <stdlib.h>

int iterate(int number)
{
    int product = 0;

    for (int i = 1; i <= number; i++) {
        if (product == 0) {
            product = 1;
            continue;
        }
        product = product * i;
    }
    return product;
}

int rekursive(int number)
{
    if (number < 0) {
        return 0;
    }
    if (number == 0) {
        return 1;
    }

    return number * rekursive(number - 1);

}

int main()
{
    fprintf(stderr, "product: %d\n", iterate(10));
    fprintf(stderr, "rekursive: %d\n", rekursive(10));
    return 0;
}

