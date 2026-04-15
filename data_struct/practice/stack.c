#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* A;
    int top;
    int capacity;
} stack;

void stack_init(stack* S){
    S->top = -1;
}

int stack_empty(stack* S){
    if (S->top == -1){
        return -1;
    }
    return 1;
}
int stack_full(stack* S){
    if (S->top == S->capacity-1){
        return -1;
    }
    return 1;
}

// push 
int push(stack* S, int key){
    if (stack_full(S) == -1){
        return -1;
    }
    S->A[(++S->top)] = key;
    return 1;
}

int pop(stack* S){
    if (stack_empty(S) == -1){
        return -1;
    }
    int k = S->A[S->top];
    S->top = S->top - 1; // this was the error from first implementation
    return k;
}

int main (){
    stack S;
    stack_init(&S);
    int n;
    scanf("%d", &n);
    S.capacity = n;
    S.A = malloc(n * sizeof(int)); // this was the error from first implementation
    char ch;
    int x;

    int outputs[1000];
    int out_count = 0;
    while(1) {
        scanf(" %c", &ch); // this was the error from first implementation; "%c" wrong and " %c" is correct
        if (ch == 't')
            break;
        
        switch(ch){
            case 'i':
                scanf("%d", &x); // this was the error from first implementation
                if (x < -100000 || x > 100000)
                    outputs[out_count++] = -1;
                else{
                    int temp = push(&S, x);
                    if (temp == -1)
                        outputs[out_count++] = temp;
                }
                break;
            case 'd':
                outputs[out_count++] = pop(&S);
                break;
            case 'e':
                outputs[out_count++] = stack_empty(&S);
                break;
            default:
                outputs[out_count++] = -1;
        }
    }

    for (int i = 0; i< out_count; i++){
        printf("%d\n", outputs[i]);
    }
    free(S.A); // this was the error from first implementation

    return 0;
}