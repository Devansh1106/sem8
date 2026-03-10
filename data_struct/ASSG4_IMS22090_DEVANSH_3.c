// Postfix expression evaluation in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

int stack[MAX];
int top = -1;

void push(int val) {
    if (top < MAX - 1) {
        stack[++top] = val;
    }
}

int pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return 0;
}

int EvaluatePostfix(char* expr) {
    char* token = strtok(expr, " ");
    
    while (token != NULL) {
        if (isdigit(token[0])) {
            push(atoi(token));
        } 
        else {
            int b = pop();
            int a = pop();
            int result;
            
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }
            push(result);
        }
        token = strtok(NULL, " ");
    }
    
    return pop();
}

int main() {
    char expr[MAX];
    fgets(expr, MAX, stdin);
    expr[strcspn(expr, "\n")] = '\0';
    
    char expr_copy[MAX];
    strcpy(expr_copy, expr);
    
    int result = EvaluatePostfix(expr_copy);
    printf("%d\n", result);
    
    return 0;
}