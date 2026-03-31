#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *left, *right, *parent;
} Node;

// ---------- BST FUNCTIONS ----------

Node* CreateNode(int k) {
    Node* x = (Node*)malloc(sizeof(Node));
    x->key = k;
    x->left = x->right = x->parent = NULL;
    return x;
}

Node* Search(Node* T, int k) {
    if (T == NULL || T->key == k)
        return T;

    if (k < T->key)
        return Search(T->left, k);
    else
        return Search(T->right, k);
}

Node* Insert(Node* T, Node* x) {
    Node* y = NULL;
    Node* curr = T;

    while (curr != NULL) {
        y = curr;
        if (x->key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }

    x->parent = y;

    if (y == NULL)
        return x;

    if (x->key < y->key)
        y->left = x;
    else
        y->right = x;

    return T;
}

Node* TreeMinimum(Node* x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

Node* Transplant(Node* T, Node* u, Node* v) {
    if (u->parent == NULL)
        T = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;

    return T;
}

Node* Delete(Node* T, Node* x) {
    if (x->left == NULL) {
        T = Transplant(T, x, x->right);
    }
    else if (x->right == NULL) {
        T = Transplant(T, x, x->left);
    }
    else {
        Node* y = TreeMinimum(x->right);

        if (y->parent != x) {
            T = Transplant(T, y, y->right);
            y->right = x->right;
            if (y->right)
                y->right->parent = y;
        }

        T = Transplant(T, x, y);
        y->left = x->left;
        if (y->left)
            y->left->parent = y;
    }

    return T;
}

// ---------- TRAVERSALS INTO BUFFER ----------

void Inorder(Node* T, char *buf) {
    if (T != NULL) {
        Inorder(T->left, buf);
        char temp[32];
        sprintf(temp, "%d ", T->key);
        strcat(buf, temp);
        Inorder(T->right, buf);
    }
}

void Preorder(Node* T, char *buf) {
    if (T != NULL) {
        char temp[32];
        sprintf(temp, "%d ", T->key);
        strcat(buf, temp);
        Preorder(T->left, buf);
        Preorder(T->right, buf);
    }
}

void Postorder(Node* T, char *buf) {
    if (T != NULL) {
        Postorder(T->left, buf);
        Postorder(T->right, buf);
        char temp[32];
        sprintf(temp, "%d ", T->key);
        strcat(buf, temp);
    }
}

// ---------- MAIN ----------

int main() {
    Node* T = NULL;

    // output buffer (large enough)
    char output[1000000] = "";
    char line[10000];

    char op;
    int k;

    while (1) {
        if (scanf(" %c", &op) == EOF)
            break;

        if (op == 'e')
            break;

        line[0] = '\0';  // reset line buffer

        if (op == 'a') {
            scanf("%d", &k);
            Node* x = CreateNode(k);
            T = Insert(T, x);
        }

        else if (op == 'd') {
            scanf("%d", &k);
            Node* x = Search(T, k);

            if (x == NULL) {
                strcat(line, "-1");
            } else {
                char temp[32];
                sprintf(temp, "%d", x->key);
                strcat(line, temp);
                T = Delete(T, x);
                free(x);
            }
            strcat(line, "\n");
            strcat(output, line);
        }

        else if (op == 's') {
            scanf("%d", &k);
            Node* x = Search(T, k);

            if (x == NULL)
                strcat(line, "-1\n");
            else
                strcat(line, "1\n");

            strcat(output, line);
        }

        else if (op == 'i') {
            Inorder(T, line);
            strcat(line, "\n");
            strcat(output, line);
        }

        else if (op == 'p') {
            Preorder(T, line);
            strcat(line, "\n");
            strcat(output, line);
        }

        else if (op == 't') {
            Postorder(T, line);
            strcat(line, "\n");
            strcat(output, line);
        }
    }

    // print everything at the end
    printf("%s", output);

    return 0;
}