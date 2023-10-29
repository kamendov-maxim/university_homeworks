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
char top(const Stack * const stack, StackErrorCode * const errorCode);
bool isEmpty(const Stack * const stack);
void deleteStack(Stack **stack);
StackErrorCode printStack(const Stack * stack);
