/*circular queue (its size is always n-1)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int head;
    int tail;
    int* A;
    int size;
} queue;

int queue_full(queue* Q){
    if((Q->tail + 1)% Q->size == Q->head){
        return -1;
    }
    return 0;
}

int queue_empty(queue* Q){
    if(Q->tail == Q->head){
        return -1;
    }
    return 0;
}

int enqueue(queue* Q, int k){
    if(queue_full(Q) == -1){
        return -1;
    }
    Q->A[Q->tail] = k;
    Q->tail = (Q->tail + 1)% Q->size;
    return 0;
}

int dequeue(queue* Q){
    if (queue_empty(Q) == -1){
        return -1;
    }
    int del = Q->A[Q->head];
    Q->head = (Q->head + 1)% Q->size;
    return del;
}   

int main(){
    int n;
    scanf("%d", &n);
    queue Q;
    Q.A = (int*)malloc(n * sizeof(int));
    Q.size = n;
    Q.head = 0;
    Q.tail = 0;

    char op;
    int val;
    int outputs[1000];
    int count = 0;
    while (scanf(" %c", &op) == 1){
        if (op == 'i'){
            scanf("%d", &val);
            int result = enqueue(&Q, val);
            if (result == -1)
                outputs[count++] = -1;
        }
        else if (op == 'd'){
            int result = dequeue(&Q);
            if (result == -1)
                outputs[count++] = -1;
            else
                outputs[count++] = result;
        }
        else if (op == 'f'){
            int result = queue_full(&Q);
            if (result == -1)
                outputs[count++] = -1;
            else
                outputs[count++] = 1;
        }
        else if (op == 'e'){
            int result = queue_empty(&Q);
            if (result == -1)
                outputs[count++] = -1;
            else
                outputs[count++] = 1;
        }
        else if (op == 't')
            break;
    }

    for(int i = 0; i < count; i++){
        printf("%d\n", outputs[i]);
    }
    free(Q.A);
    return 0;
}