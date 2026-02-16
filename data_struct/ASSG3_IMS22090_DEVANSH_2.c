#include <stdio.h>
#include <stdlib.h>

// Stack structure 
typedef struct {
    int top;
    int capacity;
    int *A;
} Stack;


// Stack-Empty(S) 
int STACK_EMPTY(Stack *S) {
    return (S->top == -1);
}

// Stack-Full(S) 
int STACK_FULL(Stack *S) {
    return (S->top == S->capacity - 1);
}

// Push(S, k) 
void PUSH(Stack *S, int k) {
    if (STACK_FULL(S)) {
        return;
    }
    S->A[++(S->top)] = k;
}

// Pop(S) 
int POP(Stack *S) {
    if (STACK_EMPTY(S)) {
        return -1;
    }
    return S->A[(S->top)--];
}


int main() {
    int n;
    scanf("%d", &n);

    if (n < 0 || n > 100000) {
        printf("-1\n");
        return 0;
    }


    Stack S;
    S.capacity = n;
    S.top = -1;
    S.A = (int *)malloc(n * sizeof(int));

    // Store outputs 
    int outputs[100000];
    int out_count = 0;

    char ch;
    int x;

    while (1) {
        scanf(" %c", &ch);

        if (ch == 't')
            break;

        switch (ch) {

            case 'i':
                scanf("%d", &x); 
                if (x < -1000000 || x > 1000000) {
                    outputs[out_count++] = -1;
                }
                else if (STACK_FULL(&S)) {
                    outputs[out_count++] = -1;
                }
                else {
                    S.A[++S.top] = x;
                }
                break;

            case 'd':
                outputs[out_count++] = POP(&S);
                break;

            case 'e':
                if (STACK_EMPTY(&S))
                    outputs[out_count++] = -1;
                else
                    outputs[out_count++] = 1;
                break;
            default:
                outputs[out_count++] = -1;
                break;
        }
    }

    // Print everything after termination 
    for (int i = 0; i < out_count; i++) {
        printf("%d\n", outputs[i]);
    }

    free(S.A);
    return 0;
}
