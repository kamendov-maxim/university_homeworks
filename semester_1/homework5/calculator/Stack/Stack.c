#include <stdlib.h>

#include "Stack.h"

typedef struct Node
{
    struct Node *next;
    float value;

} Node;

typedef struct Stack
{
    Node *head;
} Stack;

Stack *createStack(void)
{
    return calloc(1, sizeof(Stack));
}

void deleteStack(Stack **stack)
{
    Node *currentNode = (*stack)->head;
    while (currentNode != NULL)
    {
        Node *temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }
    free(*stack);
    *stack = NULL;
}

ErrorCode addElement(Stack *const stack, const float value)
{
    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return memoryErrorStack;
    }
    newNode->value = value;
    if (stack->head != NULL)
    {
        newNode->next = stack->head;
    }
    stack->head = newNode;

    // Node **currentNode = &(stack->head);
    // for (; *currentNode != NULL; currentNode = &((*currentNode)->next))
    //     ;
    // *currentNode = newNode;
    return okStack;
}

float getElement(Stack *const stack, ErrorCode *errorCode)
{
    if (stack->head == NULL)
    {
        *errorCode = emptyStack;
        return 0;
    }

    Node *temp = stack->head;
    stack->head = temp->next;
    float value = temp->value;
    free(temp);
    *errorCode = okStack;
    return value;
}
