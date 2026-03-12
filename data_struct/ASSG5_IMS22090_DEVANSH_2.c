#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *A;
    int head;
    int tail;
    int size;
} Queue;

int QueueFull(Queue *Q) {
    if ((Q->tail + 1) % Q->size == Q->head) // means queue is full
        return -1;
    return 1;
}

int QueueEmpty(Queue *Q) {
    if (Q->head == Q->tail) // means queue is empty
        return -1;
    return 1;
}

int Enqueue(Queue *Q, int k) {
    if (QueueFull(Q) == -1)
        return -1;

    Q->A[Q->tail] = k;
    Q->tail = (Q->tail + 1) % Q->size; // increment tail in circular manner

    return 0;
}

int Dequeue(Queue *Q) {
    if (QueueEmpty(Q) == -1)
        return -1;

    int val = Q->A[Q->head];
    Q->head = (Q->head + 1) % Q->size; // increment head in circular manner

    return val;
}

int main() {
    int n;
    scanf("%d", &n);

    Queue Q;
    Q.size = n;
    Q.head = 0;
    Q.tail = 0;

    Q.A = (int*)malloc(sizeof(int) * n);

    char op;
    int k;

    // Store outputs
    int outputs[10000];
    int out_count = 0;

    while (scanf(" %c", &op) == 1) {

        if (op == 'i') {
            scanf("%d", &k);
            int a = Enqueue(&Q, k);
            if (a == -1)
                outputs[out_count++] = a;
        }

        else if (op == 'd') {
            outputs[out_count++] = Dequeue(&Q);
        }

        else if (op == 'f') {
            outputs[out_count++] = QueueFull(&Q);
        }

        else if (op == 'e') {
            outputs[out_count++] = QueueEmpty(&Q);
        }

        else if (op == 't') {
            break;
        }
    }

    // Print all outputs
    for (int i = 0; i < out_count; i++) {
        printf("%d\n", outputs[i]);
    }

    free(Q.A);

    return 0;
}