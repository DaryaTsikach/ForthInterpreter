#include "stack.h"
#include <string.h>
#include "constants.h"

struct StackNode* newNode(short int data) {
    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode*));
    if (node == NULL)
        return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

int isEmpty(struct StackNode* root) {
    return !root;
}

void push(struct StackNode** root, short int data) {
    struct StackNode* newStackNode = newNode(data);
    if (newStackNode == NULL)
        exit(MEMORY_EXCEPTION);
    newStackNode->next = *root;
    *root = newStackNode;
}

short int pop(struct StackNode** root) {
    if (isEmpty(*root)) {
        exit(STACK_EXCEPTION);
    }
    struct StackNode* tmp = *root;
    short int value = tmp->data;
    *root = (*root)->next;
    free(tmp);
    return value;
}

short int peek(struct StackNode* root) {
    if (isEmpty(root)) {
        exit(STACK_EXCEPTION);
    }
    return root->data;
}
