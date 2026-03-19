#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    struct node* next;
} node;

typedef struct {
    node* tail;
} list;

struct node* create_node(int k){
    node* x = (node*)malloc(sizeof(node));
    x->key = k;
    x->next = NULL;
    return x;
}

void list_insert_front(list* L, node* x){
    if (L->tail == NULL){
        L->tail = x;
        x->next = NULL;
        return;
    }
    node* temp = L->tail;
    L->tail = x;
    x->next = temp->next;
}

void list_insert_tail(list* L, node* x){
    if (L->tail == NULL){
        L->tail =  x;
        L->tail->next = NULL;
        return;
    }
    node* temp = L->tail;
    L->tail->next = x;
    x->next = temp->next;
    return;
}

struct node* list_search(list* L, int k){
    if(L->tail == NULL){
        return NULL;
    }
    if (L->tail->key == k){
        return L->tail;
    }
    node* temp = L->tail->next;
    while(temp != L->tail){
        if (temp->key == k){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void list_insert_after(list* L, node* x, node* y){
    node* temp = y->next;
    y->next = x;
    x->next = temp;
    if (y == L->tail){
        L->tail = x;
    }
}

void list_insert_before(list* L, node* x, node* y){
    node* temp = y;
    while(temp->next != y){
        temp = temp->next;
    }
    temp->next = x;
    x->next = y;
}

void list_delete(list* L, node* x){
    node* temp = x;
    while(temp->next != x){
        temp = temp->next;
    }
    temp->next = x->next;
}

int list_delete_first(list* L){
    if (L->tail == NULL)
        return -1;
    node* temp = L->tail->next;
    int val = temp->key;
    L->tail->next = temp->next;
    return val;
}

// this is incomplete
int list_delete_last(list* L){
    node* temp = L->tail;
    while (temp->next != L->tail)
    {
        temp = temp->next;
    }
    node* temp1 = temp->next;
    temp->next = temp1->next;    
}

int main (){
    char op;
    list L;
    L.tail = (node*)malloc(sizeof(node*));

    while(scanf("%c", &op) == 1){
        if (op == 'f'){
            int key;
            scanf("%d", &key);
            node* new_node = create_node(key);
            list_insert_front(&L, new_node);
        }
        else if (op == 't'){
            int key;
            scanf("%d", &key);
            node* new_node = create_node(key);
            list_insert_tail(&L, new_node);
        }
    }

    return 0;
}