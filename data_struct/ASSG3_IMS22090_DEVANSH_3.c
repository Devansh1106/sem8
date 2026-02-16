#include <stdio.h>
#include <stdlib.h>

// Node structure 
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Stack structure 
typedef struct {
    Node* top;
} Stack;


// Create-Node(k) 
Node* CREATE_NODE(int k) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = k;
    newNode->next = NULL;
    return newNode;
}

// Stack-Empty(S) 
int STACK_EMPTY(Stack* S) {
    return (S->top == NULL);
}

// Push(S, x) 
void PUSH(Stack* S, Node* x) {
    x->next = S->top;
    S->top = x;
}

// Pop(S) 
int POP(Stack* S) {
    if (STACK_EMPTY(S))
        return -1;

    Node* temp = S->top;
    int value = temp->data;
    S->top = temp->next;
    free(temp);
    return value;
}


// Main 
int main() {
    Stack S;
    S.top = NULL;

    char ch;
    int x;

    // Store outputs 
    int outputs[100000];
    int out_count = 0;

    while (1) {
        scanf(" %c", &ch);

        if (ch == 't')
            break;

        switch (ch) {

            case 'i':
                scanf("%d", &x);
            if (x < -1000000 || x > 1000000) {
                outputs[out_count++] = -1;
            } else {
                PUSH(&S, CREATE_NODE(x));
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

    // Print all outputs after termination 
    for (int i = 0; i < out_count; i++) {
        printf("%d\n", outputs[i]);
    }

    return 0;
}
