#include <stdio.h>
// #include <math.h>

int main()
{
    int n, count=0, k;
    scanf("%d", &n);
    int A[n], seen[n];
    int index[n];
    int flag=0, flag2 = 0;
    for (size_t i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
    for (size_t i = 0; i < n; i++)
    {
        k = 0;
        count = 0;
        for (size_t p = 0; p < i; p++){
            if (A[p] == A[i]){
                flag2 = 1;
            }
            if (flag2 == 1) {
                continue;
            }
        }
        for (size_t j = 0; j < n; j++)
        {
            if (A[i] == A[j]){
                count++;
                index[k] = j;
                k++;
            }
        }
        // printf("%d\n", count);
        if (count > 1){
            printf("%d ", A[i]);
            for (size_t m = 0; m < count; m++){
                printf("%d ", index[m]);
            }
            printf("%d\n", count);
            flag = 1;
        }
    }
    if (flag == 0){
        printf("-1");
    }
    return 0;
}