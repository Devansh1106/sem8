// palindrome

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10000

// Stack structure
typedef struct {
    char arr[MAX];
    int top;
} Stack;

// Initialize stack
void init(Stack *s) {
    s->top = -1;
}

// Push operation
void push(Stack *s, char c) {
    if (s->top == MAX - 1) {
        return; // stack overflow
    }
    s->arr[++(s->top)] = c;
}

// Pop operation
char pop(Stack *s) {
    if (s->top == -1) {
        return '\0'; // stack underflow
    }
    return s->arr[(s->top)--];
}

// Function to check palindrome
int IsPalindrome(char str[]) {
    Stack s;
    init(&s);

    int n = strlen(str);

    // Push all characters to stack
    for (int i = 0; i < n; i++) {
        if (!isalpha(str[i])){
            return 0;
        }
        push(&s, str[i]);
    }

    // Compare popped characters
    for (int i = 0; i < n; i++) {
        if (str[i] != pop(&s)) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char str[MAX];

    scanf("%s", str);

    printf("%d\n", IsPalindrome(str));

    return 0;
}