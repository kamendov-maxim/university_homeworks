#pragma once

typedef struct Stack Stack;
typedef enum ErrorCode
{
    ok,
    memoryError,
    emptyStack
} ErrorCode;

Stack *createStack(void);
void deleteStack(Stack *const stack);
ErrorCode addElement(Stack *const stack, const int value);
int getElement(Stack *const stack, ErrorCode *errorCode);
