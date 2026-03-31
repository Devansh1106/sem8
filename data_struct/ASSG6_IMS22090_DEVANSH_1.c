#include <stdio.h>
#include <stdlib.h>

// swap
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Max-Heapify (recursive)
void MaxHeapify(int A[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest]) {
        largest = left;
    }

    if (right < n && A[right] > A[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&A[i], &A[largest]);
        MaxHeapify(A, n, largest);
    }
}

// Build Max Heap
void BuildMaxHeap(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(A, n, i);
    }
}

// Heap Sort
void HeapSort(int A[], int n) {
    BuildMaxHeap(A, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&A[0], &A[i]);
        MaxHeapify(A, i, 0);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int* A = (int *)malloc(n * sizeof(int));
    int count = 0;

    for (int i = 0; i < n; i++) {
        // check for input value to be in -10^3 to 10^3
        scanf("%d", &A[i]);
        count++;
        if (A[i] < -1000 || A[i] > 1000) {
            printf("-1\n");
            free(A);
            return 0;
        }
    }

    HeapSort(A, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    free(A);
    return 0;
}