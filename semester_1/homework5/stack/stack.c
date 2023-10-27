#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

typedef struct Stack
{
    char element;
    struct Stack *previous;
} Stack;

Stack *createStack(StackErrorCode *errorCode)
{
    Stack *stack = calloc(1, sizeof(Stack));
    if (stack == NULL)
    {
        *errorCode = outOfMemory;
        return stack;
    }
    *errorCode = ok;
    return stack;
}

StackErrorCode push(Stack **stack, char element)
{
    Stack *temp = calloc(1, sizeof(Stack));
    if (temp == NULL)
    {
        return outOfMemory;
    }
    temp->element = element;
    temp->previous = *stack;
    *stack = temp;
    return ok;
}

char pop(Stack **stack, StackErrorCode *errorCode)
{
    if (*stack == NULL)
    {
        *errorCode = stackIsEmpty;
        return '\0';
    }

    *errorCode = ok;
    char value = (*stack)->element;

    Stack *temp;
    temp = (*stack)->previous;
    free(*stack);
    (*stack) = temp;
    return value;
}

char top(Stack *stack, StackErrorCode *errorCode)
{
    if (isEmpty(stack))
    {
        *errorCode = stackIsEmpty;
        return '\0';
    }
    *errorCode = ok;
    return stack->element;
}

bool isEmpty(Stack *stack)
{
    return stack->element == NULL;
}

void deleteStack(Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    Stack *current = stack;
    Stack *next = NULL;
    while (current->previous != NULL)
    {
        next = current->previous;
        free(current);
        current = next;
    }
    free(next);
}


StackErrorCode printStack(Stack *stack)
{
    Stack *temp = stack;
    while (temp->previous != NULL)
    {
        char currentElement = temp->element;
        printf("%c ", currentElement);
        temp = temp->previous;
    }
    printf("\n");
    return ok;
}

void clearStack(Stack **stack)
{
    while (!isEmpty(*stack))
    {
        StackErrorCode errorCode = ok;
        pop(stack, &errorCode);
        if (errorCode == stackIsEmpty)
        {
            break;
        }
    }
}
