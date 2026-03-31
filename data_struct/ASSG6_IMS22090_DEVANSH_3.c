#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char system_id[50];
    char filename[50];
    int numPages;
    float size;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Create new node
Node* CreateNode(char* s1, char* s2, int n, float size) {
    Node* x = (Node*)malloc(sizeof(Node));
    strcpy(x->system_id, s1);
    strcpy(x->filename, s2);
    x->numPages = n;
    x->size = size;
    x->next = NULL;
    return x;
}

// AddRequest (enqueue)
void AddRequest(Queue* Q, char* s1, char* s2, int n, float size) {
    Node* x = CreateNode(s1, s2, n, size);

    if (Q->rear == NULL) {
        Q->front = Q->rear = x;
        return;
    }

    Q->rear->next = x;
    Q->rear = x;
}

// ExtractNextRequest (dequeue)
void ExtractNextRequest(Queue* Q, char* line) {
    if (Q->front == NULL) {
        strcat(line, "-1\n");
        return;
    }

    Node* temp = Q->front;

    char buf[100];
    sprintf(buf, "%s\n", temp->system_id);
    strcat(line, buf);

    Q->front = Q->front->next;

    if (Q->front == NULL)
        Q->rear = NULL;

    free(temp);
}

// ListRequests
void ListRequests(Queue* Q, char* line) {
    if (Q->front == NULL) {
        strcat(line, "-1\n");
        return;
    }

    Node* curr = Q->front;
    char buf[200];

    while (curr != NULL) {
        sprintf(buf, "%s %s %d %.1f ", 
                curr->system_id, 
                curr->filename, 
                curr->numPages, 
                curr->size);
        strcat(line, buf);
        curr = curr->next;
    }

    strcat(line, "\n");
}

// Main
int main() {
    Queue Q;
    Q.front = Q.rear = NULL;

    char output[1000000] = "";
    char line[10000];

    char op;
    char s1[50], s2[50];
    int n;
    float size;

    while (1) {
        if (scanf(" %c", &op) == EOF)
            break;

        if (op == 't')
            break;

        line[0] = '\0';  // reset per-operation buffer

        if (op == 'a') {
            scanf("%s %s %d %f", s1, s2, &n, &size);
            AddRequest(&Q, s1, s2, n, size);
        }

        else if (op == 'e') {
            ExtractNextRequest(&Q, line);
            strcat(output, line);
        }

        else if (op == 'l') {
            ListRequests(&Q, line);
            strcat(output, line);
        }
    }

    // print all outputs at end
    printf("%s", output);

    return 0;
}