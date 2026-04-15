- Assignment 3: Single linked list and Stack
- Assignment 4: Palindrom, Infix2postfix; Postfix evaluation, Doubly Linked list
- Assignment 5: Circular linked list, circular queue
- Assignment 6: Binary search tree,  queue using a singly linked list (printing service)


```c
fgets(str, 1000, stdin);
str[strcspn(str, "\n")] = '\0';
// call function and then inside function is below
char* token = strtok(str, " ");
while(token != NULL){
    if (isdigit(token[0]))
        push(&S, stoi(token));
    else{
        // b is first; this will affect the result
        int b = pop();
        int a = pop();
        switch(token[0]){
            case '+':
                // code
        }
        push(&S, res);
    }
    token = strtok(NULL, " ");
}
```

- assignment 6, ques: 2

```c
// similar is preorder and inorder
void postorder(node* T, char* buf){
    if (T != NULL){
        postorder(T->left, buf);
        postorder(T->right, buf);
        char temp[32];
        sprintf(temp, "%d ", T->key);
        strcat(buf, temp);
    }
```

```c
    char buf[100];
    sprintf(buf, "%s\n", temp->system_id);
    strcat(line, buf);
```

```c
    if (Q->front == NULL) {
        strcat(line, "-1\n");
        return;
    }
```

- printing requests:

```c
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
```
