#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int merge_sort(int* A, int p, int r);
unsigned int merge(int* A, int p, int q, int r);
void print(int* A, int n);

int main()
{
    int n;
    int temp;
    scanf("%d", &n);


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
    unsigned int count = merge_sort(A, 0, n-1);
    print(A, n);
    printf("%d\n", count);

    free(A);
    return 0;
}

unsigned int merge_sort(int* A, int p, int r){
    if (p < r){
        int q = (p+r)/2;
        merge_sort(A, p, q);
        merge_sort(A, q+1, r);
        unsigned int count = merge(A, p, q, r);
        return count;
    }
}

unsigned int merge(int* A, int p, int q, int r){
    unsigned int n = r-p +1;
    unsigned int count = 0;
    int mid = 0;
    int* A_1;
    int* A_2;
    
    if (n % 2 == 0){ 
        mid = n/2; 
    }
    else {
        mid = (n/2) + 1; 
    }

    A_1 = malloc(mid * sizeof(int));
    A_2 = malloc((n-mid) * sizeof(int));
    for (size_t i = 0; i<mid; i++){
        A_1[i] = A[p+i];
    }
    for (size_t i = 0; i<=r-p-mid; i++){
        A_2[i] = A[p+mid+i];
    }
    size_t i = 0; size_t j = 0, k = p;
    int n1 = q-p+1, n2 = r-q;
    A_1[n1] = INT_MAX;
    A_2[n2] = INT_MAX;
    for (int k = p; k <= r; k++){
        count++;
        if (A_1[i] <= A_2[j]){
            A[k] = A_1[i];
            i++;
        }
        else{
            A[k] = A_2[j];
            j++;
        }
    }
    free(A_1);
    free(A_2);
    return count;
}

void print(int* A, int n){
    for(size_t i = 0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}
