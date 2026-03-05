#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
} List;

Node* CREATE_NODE(int k) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->key = k;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

Node* LIST_SEARCH(List *L, int k) {
    Node *current = L->head;
    while (current != NULL) {
        if (current->key == k)
            return current;
        current = current->next;
    }
    return NULL;
}

void LIST_INSERT_FRONT(List *L, Node *x) {
    x->next = L->head;
    x->prev = NULL;
    if (L->head != NULL)
        L->head->prev = x;
    L->head = x;
}

void LIST_INSERT_TAIL(List *L, Node *x) {
    x->next = NULL;
    if (L->head == NULL) {
        x->prev = NULL;
        L->head = x;
        return;
    }
    Node *current = L->head;
    while (current->next != NULL)
        current = current->next;
    current->next = x;
    x->prev = current;
}

void LIST_INSERT_AFTER(List *L, Node *x, Node *y) {
    x->next = y->next;
    x->prev = y;
    if (y->next != NULL)
        y->next->prev = x;
    y->next = x;
}

void LIST_INSERT_BEFORE(List *L, Node *x, Node *y) {
    x->prev = y->prev;
    x->next = y;
    if (y->prev != NULL)
        y->prev->next = x;
    else
        L->head = x;
    y->prev = x;
}

int LIST_DELETE(List *L, Node *x) {
    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        L->head = x->next;
    if (x->next != NULL)
        x->next->prev = x->prev;
    int key = x->key;
    free(x);
    return key;
}

int LIST_DELETE_INITIAL(List *L) {
    if (L->head == NULL)
        return -1;
    return LIST_DELETE(L, L->head);
}

int LIST_DELETE_LAST(List *L) {
    if (L->head == NULL)
        return -1;
    Node *current = L->head;
    while (current->next != NULL)
        current = current->next;
    return LIST_DELETE(L, current);
}

int main() {
    List L;
    L.head = NULL;
    char op;
    int k, k2;

    while (scanf(" %c", &op) == 1) {
        if (op == 'f') {
            scanf("%d", &k);
            Node *x = CREATE_NODE(k);
            LIST_INSERT_FRONT(&L, x);
        } else if (op == 't') {
            scanf("%d", &k);
            Node *x = CREATE_NODE(k);
            LIST_INSERT_TAIL(&L, x);
        } else if (op == 'a') {
            scanf("%d %d", &k, &k2);
            Node *y = LIST_SEARCH(&L, k2);
            if (y != NULL) {
                Node *x = CREATE_NODE(k);
                LIST_INSERT_AFTER(&L, x, y);
            }
        } else if (op == 'b') {
            scanf("%d %d", &k, &k2);
            Node *y = LIST_SEARCH(&L, k2);
            if (y != NULL) {
                Node *x = CREATE_NODE(k);
                LIST_INSERT_BEFORE(&L, x, y);
            }
        } else if (op == 'd') {
            scanf("%d", &k);
            Node *x = LIST_SEARCH(&L, k);
            if (x != NULL)
                printf("%d\n", LIST_DELETE(&L, x));
            else
                printf("-1\n");
        } else if (op == 'i') {
            int deleted = LIST_DELETE_INITIAL(&L);
            printf("%d\n", deleted);
        } else if (op == 'l') {
            int deleted = LIST_DELETE_LAST(&L);
            printf("%d\n", deleted);
        } else if (op == 's') {
            scanf("%d", &k);
            if (LIST_SEARCH(&L, k) != NULL)
                printf("1\n");
            else
                printf("-1\n");
        } else if (op == 'e') {
            break;
        }
    }

    return 0;
}