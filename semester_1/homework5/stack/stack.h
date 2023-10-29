#pragma once

#include <stdbool.h>

typedef struct Stack Stack;

typedef enum StackErrorCode
{
    ok,
    stackIsEmpty,
    outOfMemory,
    PointerIsNull
} StackErrorCode;

StackErrorCode push(Stack **const stack, const char element);
StackErrorCode pop(Stack **stack);
char top(Stack *stack, StackErrorCode *errorCode);
bool isEmpty(Stack *stack);
void deleteStack(Stack **stack);
StackErrorCode printStack(Stack *stack);
