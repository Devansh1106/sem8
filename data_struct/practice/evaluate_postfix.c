#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define max 1000
int stack[max];
int top = -1;

void push(int k){
    stack[++top] = k;
}

int pop(){
    return stack[top--];
}

int eval_postfix(char* expr){
    char* token = strtok(expr, " ");
    while(token != NULL){
        if(isdigit(token[0])) {
            push(atoi(token));
        }
        else{
            int b = pop();
            int a = pop();
            int result;
            switch(token[0]){
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '/':
                    result = a / b;
                    break;
                case '*':
                    result = a * b;
                    break;
            }
            push(result);
        }
        token = strtok(NULL, " ");
    }
    return pop();
}


int main (){
    char expr[max];
    fgets(expr, max, stdin);
    expr[strcspn(expr, "\n")] = '\0';

    char expr_copy[max];
    strcpy(expr_copy, expr);

    int result = eval_postfix(expr_copy);
    printf("%d\n", result);
    return 0;
}