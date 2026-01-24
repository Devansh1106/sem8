// serial dot product

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int* a;
    int* b;
    int* c;
    time_t start, end;
    srand(3);
    a = malloc(1e9 * sizeof(int));
    b = malloc(1e9 * sizeof(int));
    c = malloc(1e9 * sizeof(int));
    for (size_t i = 0; i < 1e6; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }
    start = time(NULL);
    for (size_t i = 0; i < 1e6; i++){
        c[i] = a[i] * b[i];
    }
    end = time(NULL);
    printf("%f seconds", difftime(end, start));
    printf("\n");
    printf("%d", c[10]);

    return 0;
}