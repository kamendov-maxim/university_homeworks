#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "../stack/stack.h"
#include "calculator.h"

static ErrorCode getElems(Stack *stack, int *firstElement, int *secondElement)
{
    StackErrorCode stackErrorCode = ok;
    *secondElement = top(stack, &stackErrorCode);
    if (stackErrorCode != ok)
    {
        return PROBLEM_WITH_STACK;
    }
    // printf("p1 %d ", top(stack, &stackErrorCode));

    pop(&stack);

    // printf("%d \n", top(stack, &stackErrorCode));

    *firstElement = top(stack, &stackErrorCode);
    if (stackErrorCode != ok)
    {
        return PROBLEM_WITH_STACK;
    }
    // printStack(stack);
    // printf("p2 %d ", top(stack, &stackErrorCode));

    pop(&stack);
    
    // printf("%d \n", top(stack, &stackErrorCode));

    // printf("elems: %d %d\n", *firstElement, *secondElement);

    // printf("\n");
    // printf("res");

    // printf("%d %d\n", *firstElement, *secondElement);
    // printf("%d\n", top(stack, &stackErrorCode));
    return OK;
}

int calculator(const char expression[], ErrorCode *errorCode)
{
    int length = strlen(expression);
    if (length < 1)
    {
        *errorCode = EMPTY_LINE;
        return -1;
    }

    StackErrorCode stackErrorCode = ok;
    Stack *stack = NULL;

    int firstElement = 0;
    int secondElement = 0;
    for (int i = 0; i < length; ++i)
    {
        switch (expression[i])
        {
        case '\n':
            break;
        case ' ':
            break;
        case '/':
        {
            if (getElems(stack, &firstElement, &secondElement) != OK)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }

            int tempResult = firstElement / secondElement;
            stackErrorCode = push(&stack, tempResult);

            if (stackErrorCode != ok)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }
            break;
        }
        case '*':
        {
            if (getElems(stack, &firstElement, &secondElement) != OK)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }

            int tempResult = firstElement * secondElement;
            stackErrorCode = push(&stack, tempResult);
            if (stackErrorCode != ok)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }
            break;
        }
        case '+':
        {
            printf("plus\n");
            if (getElems(stack, &firstElement, &secondElement) != OK)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }

            int tempResult = firstElement + secondElement;
            stackErrorCode = push(&stack, tempResult);
            if (stackErrorCode != ok)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }
            break;
        }
        case '-':
        {
            if (getElems(stack, &firstElement, &secondElement) != OK)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }

            int tempResult = firstElement - secondElement;
            stackErrorCode = push(&stack, tempResult);
            if (stackErrorCode != ok)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }
            break;
        }
        default:
        {
            stackErrorCode = push(&stack, expression[i] - '0');
            if (stackErrorCode != ok)
            {
                deleteStack(&stack);
                *errorCode = PROBLEM_WITH_STACK;
                return -1;
            }
            break;
        }
        }
    }

    printStack(stack);

    int result = top(stack, &stackErrorCode);
    if (stackErrorCode != ok)
    {
        deleteStack(&stack);
        *errorCode = PROBLEM_WITH_STACK;
        return -1;
    }
    // pop(&stack);
    *errorCode = OK;
    deleteStack(&stack);
    return result;
}
