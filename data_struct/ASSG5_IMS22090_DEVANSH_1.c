#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

Node* CREATE_NODE(int k) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->key = k;
    new_node->next = NULL;
    return new_node;
}

Node* LIST_SEARCH(List *L, int k) {
    if (L->head == NULL)
        return NULL;

    Node *current = L->head;

    do {
        if (current->key == k)
            return current;
        current = current->next;
    } while (current != L->head);

    return NULL;
}

void LIST_INSERT_FRONT(List *L, Node *x) {
    if (L->head == NULL) {
        L->head = x;
        x->next = x;
        return;
    }

    Node *last = L->head;
    while (last->next != L->head)
        last = last->next;

    x->next = L->head;
    last->next = x;
    L->head = x;
}

void LIST_INSERT_TAIL(List *L, Node *x) {
    if (L->head == NULL) {
        L->head = x;
        x->next = x;
        return;
    }

    Node *last = L->head;
    while (last->next != L->head)
        last = last->next;

    last->next = x;
    x->next = L->head;
}

void LIST_INSERT_AFTER(List *L, Node *x, Node *y) {
    x->next = y->next;
    y->next = x;
}

void LIST_INSERT_BEFORE(List *L, Node *x, Node *y) {
    if (L->head == y) {
        LIST_INSERT_FRONT(L, x);
        return;
    }

    Node *current = L->head;

    while (current->next != y)
        current = current->next;

    current->next = x;
    x->next = y;
}

int LIST_DELETE(List *L, Node *x) {
    if (L->head == NULL)
        return -1;

    if (L->head == x && L->head->next == L->head) {
        int key = x->key;
        free(x);
        L->head = NULL;
        return key;
    }

    Node *current = L->head;

    while (current->next != x)
        current = current->next;

    current->next = x->next;

    if (x == L->head)
        L->head = x->next;

    int key = x->key;
    free(x);
    return key;
}

int LIST_DELETE_FIRST(List *L) {
    if (L->head == NULL)
        return -1;

    return LIST_DELETE(L, L->head);
}

int LIST_DELETE_LAST(List *L) {
    if (L->head == NULL)
        return -1;

    Node *current = L->head;

    while (current->next->next != L->head)
        current = current->next;

    Node *last = current->next;

    if (last == L->head) {
        int key = last->key;
        free(last);
        L->head = NULL;
        return key;
    }

    current->next = L->head;

    int key = last->key;
    free(last);
    return key;
}

int main() {
    List L;
    L.head = NULL;

    char op;
    int k, k2;

    // Store outputs 
    int outputs[10000];
    int out_count = 0;

    while (scanf(" %c", &op) == 1) {

        if (op == 'f') {
            scanf("%d", &k);
            Node *x = CREATE_NODE(k);
            LIST_INSERT_FRONT(&L, x);
        }

        else if (op == 't') {
            scanf("%d", &k);
            Node *x = CREATE_NODE(k);
            LIST_INSERT_TAIL(&L, x);
        }

        else if (op == 'a') {
            scanf("%d %d", &k, &k2);
            Node *y = LIST_SEARCH(&L, k2);
            if (y != NULL) {
                Node *x = CREATE_NODE(k);
                LIST_INSERT_AFTER(&L, x, y);
            }
        }

        else if (op == 'b') {
            scanf("%d %d", &k, &k2);
            Node *y = LIST_SEARCH(&L, k2);
            if (y != NULL) {
                Node *x = CREATE_NODE(k);
                LIST_INSERT_BEFORE(&L, x, y);
            }
        }

        else if (op == 'd') {
            scanf("%d", &k);
            Node *x = LIST_SEARCH(&L, k);
            if (x != NULL)
                outputs[out_count++] = LIST_DELETE(&L, x);
            else
                outputs[out_count++] = -1;
        }

        else if (op == 'i') {
            outputs[out_count++] = LIST_DELETE_FIRST(&L);
        }

        else if (op == 'l') {
            outputs[out_count++] = LIST_DELETE_LAST(&L);
        }

        else if (op == 's') {
            scanf("%d", &k);
            if (LIST_SEARCH(&L, k) != NULL)
                outputs[out_count++] = 1;
            else
                outputs[out_count++] = -1;
        }

        else if (op == 'e') {
            break;
        }
    }

    // Print all outputs
    for (int i = 0; i < out_count; i++) {
        printf("%d\n", outputs[i]);
    }

    return 0;
}