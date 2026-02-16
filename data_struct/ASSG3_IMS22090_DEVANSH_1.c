#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;


// CREATE-NODE(k) 
Node* CREATE_NODE(int k) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = k;
    newNode->next = NULL;
    return newNode;
}

// LIST-SEARCH(L, k) 
Node* LIST_SEARCH(LinkedList* L, int k) {
    Node* temp = L->head;
    while (temp != NULL) {
        if (temp->key == k)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// LIST-INSERT-FRONT(L, x) 
void LIST_INSERT_FRONT(LinkedList* L, Node* x) {
    x->next = L->head;
    L->head = x;
}


// LIST-INSERT-TAIL(L, x) 
void LIST_INSERT_TAIL(LinkedList* L, Node* x) {
    if (L->head == NULL) {
        L->head = x;
        return;
    }
    Node* temp = L->head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = x;
}


// LIST-INSERT-AFTER(L, x, y) 
void LIST_INSERT_AFTER(LinkedList* L, Node* x, int k) {
    Node* y = LIST_SEARCH(L, k);
    if (y == NULL)
        return;
    x->next = y->next;
    y->next = x;
}


// LIST-INSERT-BEFORE(L, x, y) 
void LIST_INSERT_BEFORE(LinkedList* L, Node* x, int k) {
    if (L->head == NULL)
        return;

    if (L->head->key == k) {
        LIST_INSERT_FRONT(L, x);
        return;
    }

    Node* prev = NULL;
    Node* curr = L->head;

    while (curr != NULL && curr->key != k) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return;

    prev->next = x;
    x->next = curr;
}


int LIST_DELETE(LinkedList* L, int k) {

    Node* target = LIST_SEARCH(L, k);
    if (target == NULL)
        return -1;

    Node* temp = L->head;
    Node* prev = NULL;

    while (temp != target) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL)
        L->head = target->next;
    else
        prev->next = target->next;

    int deletedKey = target->key;
    free(target);
    return deletedKey;
}



// LIST-DELETE-FIRST(L) 
int LIST_DELETE_FIRST(LinkedList* L) {
    if (L->head == NULL)
        return -1;

    Node* temp = L->head;
    L->head = temp->next;
    int deletedKey = temp->key;
    free(temp);
    return deletedKey;
}


// LIST-DELETE-LAST(L) 
int LIST_DELETE_LAST(LinkedList* L) {
    if (L->head == NULL)
        return -1;

    Node* temp = L->head;
    Node* prev = NULL;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL)
        L->head = NULL;
    else
        prev->next = NULL;

    int deletedKey = temp->key;
    free(temp);
    return deletedKey;
}


int main() {
    LinkedList L;
    L.head = NULL;

    char ch;
    int x, y;

    int outputs[1000];   // store results
    int out_count = 0;   // number of stored outputs

    while (1) {
        scanf(" %c", &ch);

        if (ch == 'e')
            break;

        switch (ch) {
            case 'f':
                scanf("%d", &x);
                if (x < -1000000 || x > 1000000) {
                    outputs[out_count++] = -1;
                } 
                else {
                    LIST_INSERT_FRONT(&L, CREATE_NODE(x));
                }
                break;
            case 't':
                scanf("%d", &x);
                if (x < -1000000 || x > 1000000) {
                    outputs[out_count++] = -1;
                } 
                else {
                    LIST_INSERT_TAIL(&L, CREATE_NODE(x));
                }
                break;
            case 'a':
                scanf("%d %d", &x, &y);
                if (x < -1000000 || x > 1000000 ||
                    y < -1000000 || y > 1000000) {
                    outputs[out_count++] = -1;
                } 
                else {
                    LIST_INSERT_AFTER(&L, CREATE_NODE(x), y);
                }
                break;
            case 'b':
                scanf("%d %d", &x, &y);
                if (x < -1000000 || x > 1000000 ||
                    y < -1000000 || y > 1000000) {
                    outputs[out_count++] = -1;
                } 
                else {
                    LIST_INSERT_BEFORE(&L, CREATE_NODE(x), y);
                }
                break;

            case 'd':
                scanf("%d", &x);
                outputs[out_count++] = LIST_DELETE(&L, x);
                break;

            case 'i':
                outputs[out_count++] = LIST_DELETE_FIRST(&L);
                break;

            case 'l':
                outputs[out_count++] = LIST_DELETE_LAST(&L);
                break;

            case 's':
                scanf("%d", &x);
                if (LIST_SEARCH(&L, x) != NULL)
                    outputs[out_count++] = 1;
                else
                    outputs[out_count++] = -1;
                break;
            default:
                outputs[out_count++] = -1;
                break;
        }
    }

    // Print everything after 'e'
    for (int i = 0; i < out_count; i++) {
        printf("%d\n", outputs[i]);
    }

    return 0;
}

