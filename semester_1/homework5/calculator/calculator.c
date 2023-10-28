#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#include "../stack/stack.h"

#define MAX 1000

typedef enum ErrorCode
{
    OK,
    problemWithStack,
    incorrectInput,
    emptyLine
} ErrorCode;

bool operation(char operand, Stack **stack);
int calculator(const char expression[], ErrorCode *errorCode);
bool test();

int main()
{
    setlocale(LC_ALL, "Rus");
    if (!test())
    {
        printf("Простите, но похоже, что программа сейчас не работает корректно\n");
        return 1;
    }

    printf("Введите арифметическое выражение в постфиксной форме: ");

    char expression[MAX] = {'\0'};
    fgets(expression, sizeof(expression), stdin);

    while (strlen(expression) < 2)
    {
        printf("\nВы не ввели выражение\nПопробуйте ещё раз\n\n");

        printf("Введите арифметическое выражение в постфиксной форме: ");

        fgets(expression, sizeof(expression), stdin);
    }

    ErrorCode errorCode = OK;
    int result = calculator(expression, &errorCode);
    if (errorCode != OK)
    {
        printf("Похоже, что-то пошло не так\n", errorCode);
        return 1;
    }
    printf("Ответ: %d", result);

    return 0;
}

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
