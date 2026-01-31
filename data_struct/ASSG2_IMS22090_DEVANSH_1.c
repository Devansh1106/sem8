#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    unsigned int n;
    scanf("%u", &n);
    getchar();
    int key = 0;
    int* A;
    int count = 0;
    int c;
    int i = 0;
    int* temp = malloc((1e9+1) * sizeof(int));
    // char/string or bounds check
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c < '0' || c > '9' || ((int)(c)) > 1000 || ((int)(c)) < -1000){
            printf("%d", (int)(c));
            printf("ji23");
            printf("-1\n");
            free(temp);
            return 0;
        }
        else{
            temp[i] = c;
            i++;
        }
    }
    for (size_t i = 0; i < 1e9+1; i++){
        while(scanf("%d", &temp[i]) != 1){
            printf("ji23");
            printf("-1\n");
            free(temp);
            return 0;
        }
        if (i+1 >= n){
            break;
        }
    }
    // count check
    printf("ji");
    if(i != n){
        printf("-1\n");
        free(temp);
        return 0;
    }
    
    int* temp_ptr = realloc(temp, n * sizeof(int));
    A = temp_ptr;
    for(int j = 1; j<n; j++){
        key = A[j];
        i = j-1;
        while(i > -1 && A[i] > key){
            A[i+1] = A[i];
            i = i-1;
        }
        A[i+1] = key;
    }
    for(size_t i = 0; i<n; i++){
        printf("%d ", A[i]);
    }
    free(temp);
    return 0;
}