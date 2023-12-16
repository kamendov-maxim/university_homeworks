#include <stdlib.h>

#include "Stack.h"

typedef struct Node
{
    struct Node* next;
    int value;

} Node;

typedef struct Stack
{
    Node *head;
} Stack;

Stack *createStack(void)
{
    return calloc(1, sizeof(Stack));
}

void deleteStack(Stack *const stack)
{
    Node *currentNode = stack->head;
    while (currentNode != NULL)
    {
        Node *temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }
    free(stack);
}

ErrorCode addElement(Stack *const stack, const int value)
{
    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return memoryError;
    }
    newNode->value = value;
    Node **currentNode = &(stack->head);
    for (; *currentNode != NULL; currentNode = &((*currentNode)->next))
        ;
    *currentNode = newNode;
    return ok;
}

int getElement(Stack *const stack, ErrorCode *errorCode)
{
    if (stack->head == NULL)
    {
        *errorCode = emptyStack;
        return 0;
    }

    Node *temp = stack->head;
    stack->head = temp->next;
    int value = temp->value;
    free(temp);
    *errorCode = ok;
    return value;
}
