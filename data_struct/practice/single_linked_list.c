#include <stdio.h>
#include <stdlib.h>

// for node
typedef struct {
    int key;
    struct node* next;
} node;

// for linkedlist
typedef struct {
    node* head;
} LinkedList;

node* create_node(int k){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->key = k;
    newNode->next = NULL;
    return newNode;
}




int main(){
    LinkedList L;
    L.head = NULL;

    char ch; // for input commands
    int outputs[1000];
    int output_count = 0;
    int x;

    while(1){
        scanf(" %c", &ch);
        if (ch == 'e')
            break;
        
        switch(ch){
            case 'f':
                scanf("%d", x);
                if (x < -100000 || x > 100000){
                    outputs[output_count++] = -1;
                }
                else {
                    list_insert_front(L, create_node(x));
                }
                break;
            
            case 'd':
                // write stuff here
        }
    }
    return 0;
}