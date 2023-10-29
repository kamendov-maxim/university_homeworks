
#include "../stack/stack.h"
#include "calculator.h"

bool test();


int calculator(const char expression[], ErrorCode *errorCode)
{
    int length = strlen(expression);
    if (length < 1)
    {
        *errorCode = emptyLine;
        return -1;
    }
    StackErrorCode stackErrorCode = ok;
    Stack *stack = createStack(&stackErrorCode);
    if (stackErrorCode != ok)
    {
        *errorCode = problemWithStack;
        return -1;
    }

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
            int firstElement = top()
            int secondElement = pop(&stack, &stackErrorCode);
            if (stackErrorCode != ok)
            {
                *errorCode = problemWithStack;
                return -1;
            }

            int firstElement = pop(&stack, &stackErrorCode);
            if (stackErrorCode != ok)
            {
                *errorCode = problemWithStack;
                return -1;
            }

            int tempResult = firstElement / secondElement;
            push(&stack, tempResult);
            break;
        }
        case '*':
        {
            int secondElement = pop(&stack, &stackErrorCode);
            if (stackErrorCode != ok)
            {
                *errorCode = problemWithStack;
                return -1;
            }

            int firstElement = pop(&stack, &stackErrorCode);
            if (stackErrorCode != ok)
            {
                *errorCode = problemWithStack;
                return -1;
            }

            int tempResult = firstElement * secondElement;
            push(&stack, tempResult);
            break;
        }
        case '+':
        {
            int secondElement = pop(&stack, &stackErrorCode);
            if (stackErrorCode != ok)
            {
                *errorCode = problemWithStack;
                return -1;
            }

            int firstElement = pop(&stack, &stackErrorCode);
            if (stackErrorCode != ok)
            {
                *errorCode = problemWithStack;
                return -1;
            }

            int tempResult = firstElement + secondElement;
            push(&stack, tempResult);
            break;
        }
        case '-':
        {
            int secondElement = pop(&stack, &stackErrorCode);
            if (stackErrorCode != ok)
            {
                *errorCode = problemWithStack;
                return -1;
            }

            int firstElement = pop(&stack, &stackErrorCode);
            if (stackErrorCode != ok)
            {
                *errorCode = problemWithStack;
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
        pop(&stack, &stackErrorCode);
        if (stackErrorCode != ok || (!isEmpty(stack)))
        {
            *errorCode = problemWithStack;
        }
    }

    return result;
}

bool test(void)
{
    ErrorCode errorCode = 0;
    const char test1[] = "2 2 +";
    if (calculator(test1, &errorCode) != 4 || errorCode != OK)
    {
        return false;
    }

    const char test2[] = "3 5 * 4 +";
    if (calculator(test2, &errorCode) != 19 || errorCode != OK)
    {
        return false;
    }

    const char test3[] = "9 4 6 2 / + -";
    if (calculator(test3, &errorCode) != 2 || errorCode != OK)
    {
        return false;
    }

    const char test4[] = "";
    if (calculator(test4, &errorCode) != -1 || errorCode != emptyLine)
    {
        return false;
    }

    return true;
}
