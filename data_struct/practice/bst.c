// bst

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    struct node* parent;
    struct node* left;
    struct node* right;
} node;

node* create_node(int key){
    node* x = (node*) malloc(sizeof(node));
    x->key = key;
    x->parent = x->left = x->right= NULL;
    return x;
}

node* search(node* T, int key){
    if (T == NULL || T->key == key){
        return T;
    }
    if (key < T->key){
        return search(T->left, key);
    }
    else 
        return search(T->right, key);
}

// minimum node in the tree
node* TreeMinimum(node* x){
    while (x != NULL){
        x = x->left;
    }
    return x;
}

// insert
node* insert(node* T, node* x){
    node* curr = T;
    node* y;
    while (curr != NULL){
        y = curr;
        if (x->key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    x->parent = y;
    if (y == NULL){
        return x;
    }
    if (x->key < y->key){
        y->left = x;
    }
    else 
        y->right = x;

    return T;
}





// traversals
void inorder(node* T, char* buf){
    if (T != NULL){
        inorder(T->left, buf);
        char temp[32];
        sprintf(temp, "%d ", T->key);
        strcat(buf, temp);
        inorder(T->right, buf);
    }
}

void preorder(node* T, char* buf){
    if (T != NULL){
        char temp[32];
        sprintf(temp, "%d ", T->key);
        strcat(buf, temp);
        preorder(T->left, buf);
        preorder(T->right, buf);
    }
}

void postorder(node* T, char* buf){
    if (T != NULL){
        postorder(T->left, buf);
        postorder(T->right, buf);
        char temp[32];
        sprintf(temp, "%d ", T->key);
        strcat(buf, temp);
    }
    
}