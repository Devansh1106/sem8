#include <stdio.h>
#include <stdlib.h>

int insertionSort(int arr[], long long n) {
    for (long long i = 1; i < n; i++) {
        int key = arr[i];
        long long j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return 0;
}

int main() {
    long long n;

    /* Read n */
    if (scanf("%lld", &n) != 1 || n <= 0 || n >= 1000000000) {
        printf("-1\n");
        return 0;
    }

    /* Guard against absurd memory requests */
    // if (n > 1000000) {  // optional safety cap
    //     printf("-1");
    //     return 0;
    // }

    int arr[n];

    /* Read exactly n integers */
    for (long long i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("-1\n");
            return 0;
        }
        if (arr[i] < -1000 || arr[i] > 1000) {
            printf("-1\n");
            return 0;
        }
    }

    /* Check for extra input */
    int extra;
    if (scanf("%d", &extra) == 1) {
        printf("-1\n");
        return 0;
    }

    insertionSort(arr, n);

    for (long long i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
