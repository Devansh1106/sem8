#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
    unsigned int n;
    scanf("%u", &n);
    if (n > 1e9){
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

    // insertion sort logic
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
    printf("\n");
    free(A);
    return 0;
}