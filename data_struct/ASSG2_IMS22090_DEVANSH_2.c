#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void quick_sort(int* A, int p, int q);
unsigned int partition(int* A, int p, int r);

int main()
{
    long long int n;
    scanf("%lld", &n);
    if (n > 1000000000LL){ // LL is for telling compiler to treat it as long long integer.
        printf("-1\n");
        return 0;
    }
    getchar();
    int key = 0;
    char line[10000];
    int* A;
    int count = 0;
    int i = 0;
    A = malloc(n * sizeof(int));

    // check for different cases!
    if (fgets(line, sizeof(line), stdin)) {        
        char* token = strtok(line, " \n");
        while (token != NULL) {
            for (size_t i = 0; i < strlen(token); i++){
                if (!isdigit(token[i])){
                    printf("-1\n");
                    return 0;
                }
            }
            int val = atoi(token);            
            if (val > 1000 || val < -1000) {
                printf("-1\n");
                return 0;
            }
            if (count < n) {
                A[count] = val;
            }
            count++;
            token = strtok(NULL, " \n");
        }
        if (count != n){
            printf("-1\n");
            return 0;
        }
    }
    quick_sort(A, 0, n-1);
    for (size_t i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    free(A);
    return 0;
}

void quick_sort(int* A, int p, int r){
    if (p < r){
        int q = partition(A, p, r);
        quick_sort(A, p, q-1);
        quick_sort(A, q+1, r);
    }
}

// in-place partition
unsigned int partition(int* A, int p, int r){
    int pivot = A[r];
    int i = p - 1;
    int temp;
    for (size_t j = p; j < r; j++){
        if (A[j] <= pivot){
            i++;
            temp = A[j];
            A[j] = A[i];
            A[i] = temp;
        }
    }
    temp = A[r];
    A[r] = A[i+1];
    A[i+1] = temp;   
    return i+1;
}