#include <stdio.h>
#include <stdlib.h>

int calc_gcd(int a, int b){
    if (a == 0){
        return b;
    }
    else if (b == 0){
        return a;
    }
    else {
        return calc_gcd(b%a, a);
    }
}

int main()
{
    int a, b;
    int gcd;
    int calc_gcd(int a, int b);
    scanf("%d %d", &a, &b);
    a = abs(a); b = abs(b);
    if (a < b){
        gcd = calc_gcd(a,b);
    }
    else if (a > b)
    {
        gcd = calc_gcd(b,a);
    }
    else{
        printf("%d", a);
    }
    
    printf("%d", gcd);

    return 0;
}