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
        return PROBLEMWITHSTACK;
    }
    pop(&stack);

    *firstElement = top(stack, &stackErrorCode);
    if (stackErrorCode != ok)
    {
        return PROBLEMWITHSTACK;
    }
    pop(&stack);

    printf("%d %d\n", *firstElement, *secondElement);
    return OK;
}

int calculator(const char expression[], ErrorCode *errorCode)
{
    int length = strlen(expression);
    if (length < 1)
    {
        *errorCode = EMPTYLINE;
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
        {
            break;
        }
        case '/':
        {
            if (getElems(stack, &firstElement, &secondElement) != OK)
            {
                deleteStack(&stack);
                *errorCode = PROBLEMWITHSTACK;
                return -1;
            }

            int tempResult = firstElement / secondElement;
            push(&stack, tempResult);
            break;
        }
        case '*':
        {
            if (getElems(stack, &firstElement, &secondElement) != OK)
            {
                deleteStack(&stack);
                *errorCode = PROBLEMWITHSTACK;
                return -1;
            }

            int tempResult = firstElement * secondElement;
            push(&stack, tempResult);
            break;
        }
        case '+':
        {
            if (getElems(stack, &firstElement, &secondElement) != OK)
            {
                deleteStack(&stack);
                *errorCode = PROBLEMWITHSTACK;
                return -1;
            }

            int tempResult = firstElement + secondElement;
            push(&stack, tempResult);
            break;
        }
        case '-':
        {
            if (getElems(stack, &firstElement, &secondElement) != OK)
            {
                deleteStack(&stack);
                *errorCode = PROBLEMWITHSTACK;
                return -1;
            }

            int tempResult = firstElement - secondElement;
            push(&stack, tempResult);
            break;
        }
        default:
        {
            push(&stack, expression[i] - '0');
            break;
        }
        }
    }

    int result = top(stack, &stackErrorCode);
    if (stackErrorCode != ok)
    {
        deleteStack(&stack);
        *errorCode = PROBLEMWITHSTACK;
        return -1;
    }
    pop(&stack);
    *errorCode = OK;
    deleteStack(&stack);
    return result;
}
