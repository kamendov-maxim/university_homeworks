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

Stack *createStack(StackErrorCode *errorCode);
StackErrorCode push(Stack **stack, char element); 
char pop(Stack **stack, StackErrorCode *errorCode); 
char top(Stack *stack, StackErrorCode *errorCode);
bool isEmpty(Stack *stack); 
void deleteStack(Stack* stack);
StackErrorCode printStack(Stack *stack);
void clearStack(Stack **stack);
