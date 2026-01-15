#include <stdio.h>
#include <math.h>

int main()
{
    int n, p;
    int sum = 0;
    int i = 0;
    int base = 8;
    scanf("%d", &n);
    while (n > 0){
        p = n % 10;
        sum += p * (pow(base, i));
        n = n/10;
        i++;
    }
    printf("%d\n", sum);
    return 0;
}