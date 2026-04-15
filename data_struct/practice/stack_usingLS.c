#include <stdio.h>
#include <stdlib.h>

typedef struct node{ // this was the error from first implementation (adding node after struct keyword)
    int data;
    struct node* next;
} node;

typedef struct{
    node* top; // same as head
} stack;


node* create_node(int key){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = key;
    newNode->next = NULL;
    return newNode;
}

int push(stack* S, int key){
    node* temp = create_node(key);
    temp->next = S->top;
    S->top = temp;
}

int pop(stack* S){ // this was the error from first implementation (use stack* always)
    node* temp = S->top;
    S->top = S->top->next;
    int k = temp->data;
    free(temp);
    return k;
}

int stack_empty(stack* S){
    if (S->top == NULL){
        return -1;
    }
    return 1;
}

int main (){
    stack S;
    S.top = NULL;

    char ch;
    int x;

    int outputs[1000];
    int out_count = 0;

    while(1) {
        scanf(" %c", &ch); // this was the error from first implementation (space before %c is important)
        if (ch == 't'){
            break;
        }
        switch (ch){
            case 'i':
                scanf("%d", &x);
                push(&S, x); // this was the error from first implementation (pass addresses in these functions)
                break;

            case 'd':
                if (stack_empty(&S) == -1)
                    outputs[out_count++] = -1;
                else{
                    outputs[out_count++] = pop(&S);
                }
                break;

            case 'e':
                int temp = stack_empty(&S);
                if (temp == -1)
                    outputs[out_count++] = temp;
                else
                    outputs[out_count++] = temp;
                break;
            default:
                outputs[out_count++] = -1;
                break;                
        }
    }

    for (int i = 0; i < out_count; i++){
        printf("%d\n", outputs[i]);
    }

    return 0;
}