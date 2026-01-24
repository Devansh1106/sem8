// Bubble sort

#include <stdio.h>
#include <stdlib.h>

int main()
{
    long int n = 0;
    int temp;
    scanf("%ld", &n);
    int* A = malloc(n * sizeof(int));
    for (size_t i = 0; i<n; i++){
        scanf("%d", &A[i]);
    }
    for (size_t i = 0; i<n; i++){
        if (A[i] > 1000 || A[i] < -1000){
            printf("-1\n");
            exit(1);
        }
    }

    for (size_t k = 0; k<n; k++){
        for (size_t i = n-1; i>k; i--){
            if (A[i] < A[i-1]){
                temp = A[i];
                A[i] = A[i-1];
                A[i-1] = temp;
            }
        }
    }

    for(size_t i = 0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}