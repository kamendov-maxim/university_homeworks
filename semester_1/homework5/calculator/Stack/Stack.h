#pragma once

typedef struct Stack Stack;
typedef enum ErrorCode
{
    okStack,
    memoryErrorStack,
    emptyStack
} ErrorCode;

Stack *createStack(void);
void deleteStack(Stack ** stack);
ErrorCode addElement(Stack *const stack, const float value);
float getElement(Stack *const stack, ErrorCode *errorCode);
