#include "stack.h"
#include <string.h>

struct StackNode* newNode(short int data) {
    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode*));
    node->data = data;
    node->next = NULL;
    return node;
}

int isEmpty(struct StackNode* root) {
    return !root;
}

void push(struct StackNode** root, short int data) {
    struct StackNode* newStackNode = newNode(data);
    newStackNode->next = *root;
    *root = newStackNode;
}

short int pop(struct StackNode** root) {
    if (isEmpty(*root)) {
        fprintf(stderr, "stack is empty \n");
        return 0;
    }
    struct StackNode* tmp = *root;
    short int value = tmp->data;
    *root = (*root)->next;
    free(tmp);
    return value;
}

short int peek(struct StackNode* root) {
    if (isEmpty(root)) {
        fprintf(stderr, "stack is empty \n");
        return 0;
    }
    return root->data;
}
