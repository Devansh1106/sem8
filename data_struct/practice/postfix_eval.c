#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int top;
    int A[1000];
} stack;

void push(stack* S, int key){
    S->A[++(S->top)] = key;
}

int pop(stack* S){
    return S->A[(S->top)--];
}

int isEmpty(stack* S){
    return (S->top == -1);
}

void postfix_eval(char* str){
    stack S;
    S.top = -1;
    char* token = strtok(str, " ");
    // int n = strlen(str);
    while(token != NULL){
        if (isdigit(token[0])){
            push(&S, atoi(token));
        }
        else{
            int b = pop(&S);
            int a = pop(&S);
            int res;
            switch(token[0]){
                case '+':
                    res = a+b;
                    break;
                case '-':
                    res = a-b;
                    break;
                case '*':
                    res = a*b;
                    break;
                case '/':
                    res = a/b;
                    break;
            }
            push(&S, res);
        }
        token = strtok(NULL, " ");
    }
    printf("%d\n", pop(&S));
}
 int main (){
    char str[1000];
    fgets(str, 1000, stdin);
    str[strcspn(str, "\n")] = '\0';
    postfix_eval(str);
    return 0;
 }