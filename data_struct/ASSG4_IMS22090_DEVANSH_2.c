#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure
typedef struct {
    char items[MAX];
    int top;
} Stack;

// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Push element to stack
void push(Stack *s, char c) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = c;
    }
}

// Pop element from stack
char pop(Stack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return '\0';
}

// Peek top element
char peek(Stack *s) {
    if (s->top >= 0) {
        return s->items[s->top];
    }
    return '\0';
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Get precedence of operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix
char* infixToPostfix(char *infix) {
    Stack s;
    initStack(&s);
    
    char *postfix = (char *)malloc(strlen(infix) + 1);
    int k = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        
        // If operand, add to postfix
        if (isalpha(c)) {
            postfix[k++] = c;
        }
        // If opening parenthesis, push to stack
        else if (c == '(') {
            push(&s, c);
        }
        // If closing parenthesis, pop until opening parenthesis
        else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s); // Remove the opening parenthesis
        }
        // If operator
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!isEmpty(&s) && peek(&s) != '(' && 
                   precedence(peek(&s)) >= precedence(c)) {
                postfix[k++] = pop(&s);
            }
            push(&s, c);
        }
    }
    
    // Pop remaining operators
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    
    postfix[k] = '\0';
    return postfix;
}

int main() {
    char infix[MAX];
    
    scanf("%s", infix);
    
    char *postfix = infixToPostfix(infix);
    printf("%s\n", postfix);
    
    free(postfix);
    return 0;
}