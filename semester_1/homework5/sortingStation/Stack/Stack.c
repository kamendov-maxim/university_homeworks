#include <stdlib.h>

#include "Stack.h"

typedef struct Node
{
    struct Node *next;
    char value;
} Node;

typedef struct Stack
{
    size_t length;
    Node *head;
} Stack;

Stack *createStack(void)
{
    return calloc(1, sizeof(Stack));
}

void deleteStack(Stack **const stack)
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

StackErrorCode addElement(Stack *const stack, const char value)
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
    ++(stack->length);

    return okStack;
}

char getElement(Stack *const stack, StackErrorCode *const errorCode)
{
    if (stack->head == NULL)
    {
        *errorCode = emptyStack;
        return 0;
    }

    Node *temp = stack->head;
    stack->head = temp->next;
    char value = temp->value;
    free(temp);
    --(stack->length);
    *errorCode = okStack;
    return value;
}

char topElement(Stack const *const stack, StackErrorCode *const errorCode)
{
    if (stack->head == NULL)
    {
        *errorCode = emptyStack;
        return '\0';
    }
    *errorCode = okStack;
    return stack->head->value;
}

static void addToString(Node * const node, char * output, size_t i)
{
    if (node == NULL)
    {
        return;
    }
    
    if (node->next == NULL)
    {
        output[i] =  node->value;
        output[i + 1] = ' ';
        return;
    }
    addToString(node->next, output, i - 2);
    output[i] = node->value;
        output[i + 1] = ' ';
}

char *createString(Stack const *const stack, StackErrorCode *errorCode)
{
    if (stack == NULL || stack->head == NULL)
    {
        *errorCode = emptyStack;
        return NULL;
    }

    char *output = (char *)malloc((stack->length) * 2 * sizeof(char));
    if (output == NULL)
    {
        *errorCode = memoryErrorStack;
        return NULL;
    }
    size_t strl = stack->length * 2;
    addToString(stack->head, output, strl - 2);
    output[strl -1 ]= '\0';
    return output;
}

