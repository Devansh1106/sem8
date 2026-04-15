#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int top;
    char A[1000];
} stack;

void push(stack* S, char key){
    S->A[++(S->top)] = key;
}

char pop(stack* S){
    return S->A[(S->top)--];
}

char peek(stack* S){
    return S->A[(S->top)];
}

int precedence(char key){
    if (key == '+' || key == '-') return 1;
    if (key == '*' || key == '/') return 2;
    return 0;
}

int isEmpty(stack* S){
    return (S->top == -1);
}

void infix2postfix(char* str){
    int n = strlen(str);
    char output[1000];
    stack S;
    S.top = -1;
    int k = 0;
    for (int i = 0; i < n; i++){
        char key = str[i];
        if (isalpha(key)){
            output[k++] = key;
        }
        else if (key == '('){
            push(&S, key);
        }
        else if (key == ')'){
            while(!isEmpty(&S) && peek(&S) != '('){ // use peek here always not pop()
                output[k++] = pop(&S);
            }
            pop(&S); // for removing the ( bracket
        } // keep all operators down there and code isEmpty()
        else if (key == '+' || key == '-' || key == '*' || key == '/'){
            while(!isEmpty(&S) && peek(&S) != '(' && precedence(peek(&S)) >= precedence(key) ){
                output[k++] = pop(&S);
            }
            push(&S, key);
        }
    }
    while(!isEmpty(&S)){ // for outputting the remaining since there can be operators left in the stack
        output[k++] = pop(&S);
    }
    output[k] = '\0'; //  for printing using %s
    printf("%s\n", output);
}

int main (){
    char str[1000];
    scanf("%s", str);
    infix2postfix(str);
    return 0;
}