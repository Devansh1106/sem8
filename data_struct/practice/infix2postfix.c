#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define max 1000

typedef struct {
    int top;
    char A[max];
} stack;

void init(stack* s){
    s->top = -1;
}

void push(stack* s, char k){
    if(s->top < max - 1)
        s->A[++(s->top)] = k;
}

char peek(stack* s){
    return s->A[s->top];
}

char pop(stack* s){
    char del;
    if (s->top != -1){
        del = s->A[s->top];
        s->top -= 1;
        return del;
    }
}

int is_empty(stack* s){
    if (s->top == -1){
        return -1;
    }
    else {
        return 0;
    }
}

int precedence(char sym){
    if (sym == '*' || sym == '/')
        return 2;
    else if (sym == '-' || sym == '+')
        return 1; 
    else
        return 0;
}

char* infix2postfix(char* s){
    stack op;
    init(&op);
    char* postfix = (char*)malloc(strlen(s) + 1);
    int k = 0;
    int i = 0;
    while(s[i] != '\0'){
        char c = s[i];
        i++;
        if (islower(c)){
            postfix[k++] = c;
        }
        else if (c == '('){
            push(&op, c);
        }
        else if (c == ')'){
            while(peek(&op) != '(' && !is_empty(&op)){
                postfix[k++] = pop(&op);
            }
            pop(&op);
        }
        else if (c == '+' || c == '*' || c == '/' || c == '-'){
            while(!is_empty(&op) && peek(&op) != '(' && precedence(peek(&op)) >= precedence(c)){
                postfix[k++] = pop(&op);
            }
            push(&op, c);
        }
    }
    while(!is_empty(&op)){
        postfix[k++] = pop(&op);
    }
    postfix[k] = '\0';
    return postfix;
}


int main (){
    char infix[max];

    scanf("%s", infix);

    char* postfix = infix2postfix(infix);
    printf("%s\n", postfix);
    return 0;
}