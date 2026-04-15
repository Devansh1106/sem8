#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int top;
    char* A;
} stack;

void push(stack* S, char key){
    S->A[++(S->top)] = key;
}

char pop(stack* S){
    char k = S->A[(S->top)--];
    return k;
}


int palindrome(char* str){
    int n = strlen(str);
    stack S;
    S.A = (char*) malloc(n * sizeof(char));
    S.top = -1;

    for (int i = 0; i < n; i++){
        char temp = str[i];
        push(&S, temp);
    }
    int flag = -1;
    for (int i = 0; i < n; i++){
        if (str[i] != pop(&S)){
            flag = 1;
            break;
        }
    }
    if (flag == 1){
        free(S.A);
        return -1;
    }
    else{
        free(S.A);
        return 1;
    }
}


int main (){
    char str[1000]; // avoid using dynamic memory allocation for easy doing
    scanf("%s", str); // there is not & symbol in string input

    int temp = palindrome(str);
    if (temp == 1)
        printf("1\n");
    else
        printf("-1\n");
    return 0;
}