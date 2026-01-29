// selection sort

#include <stdio.h>
#include <stdlib.h>

int main()
{
    long int n;
    int temp;
    scanf("%ld", &n);
    int* A = malloc(n * sizeof(int));
    for (size_t i = 0; i<n; i++){
        scanf("%d", &A[i]);
    }

    for (size_t i = 0; i<n; i++){
        if (A[i] > 1000 || A[i] < -1000){
            printf("-1\n");
            return 0;
        }
    }

    for (size_t i = 0; i<n-1; i++){
        size_t min_id = i;
        for (size_t j = i+1; j<n; j++){
            if (A[j] < A[min_id]){
                min_id = j;
            }
        }
        if (min_id != i){
            temp = A[min_id];
            A[min_id] = A[i];
            A[i] = temp;
        }
    }

    for(size_t i = 0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}