#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct StackNode;
struct StackNode {
    short int data;
    struct StackNode* next;
};

struct StackNode* newNode(short int data);

int isEmpty(struct StackNode* root);

void push(struct StackNode **root, short int data);

short int pop(struct StackNode** root);

short int peek(struct StackNode* root);


#endif // STACK_H
