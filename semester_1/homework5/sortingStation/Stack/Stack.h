#pragma once

typedef struct Stack Stack;
typedef enum StackErrorCode
{
    okStack,
    memoryErrorStack,
    emptyStack
} StackErrorCode;

// создать пустой стек
Stack *createStack(void);

// удалить стек
void deleteStack(Stack ** const stack);

// добавить элемент в стек
StackErrorCode addElement(Stack *const stack, const char value);

// взять верхний элемент из стека
char getElement(Stack *const stack, StackErrorCode * const errorCode);

// получить значение верхней ячейки стека, не удаляя ее
char topElement(Stack const *const stack, StackErrorCode *const errorCode);

// получить строку со всеми значениями стека, где самый правый элемент - самый верхний элемент стека
char *createString(Stack const *const stack, StackErrorCode * const errorCode);
