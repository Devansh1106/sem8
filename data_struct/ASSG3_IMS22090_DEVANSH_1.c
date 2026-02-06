#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* create_node(int value) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void list_insert_front(struct Node** head, int value) {
    struct Node* new_node = create_node(value);
    new_node->next = *head;
    *head = new_node;
}

void list_insert_tail(struct Node** head, int value) {
    struct Node* new_node = create_node(value);
    if (*head = NULL){
        *head = new_node;
        return;
    }
    new_node->next = *head;
    *head = new_node;
}

void list_insert_after(struct Node** head, int x, int y){

}

void list_delete(struct Node** head, int x){
    
}


int main()
{

    return 0;
}


