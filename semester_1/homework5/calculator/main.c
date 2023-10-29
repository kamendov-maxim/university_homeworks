#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../stack/stack.h"

#define MAX 1000

typedef enum ErrorCode
{
    OK,
    problemWithStack,
    incorrectInput
} ErrorCode;

bool operation(char operand, Stack **postfixMachine);
int calculator(char expression[], ErrorCode *errorCode);
bool tests();

int main()
{
    if (!tests())
    {
        return 1;
    }

    int errorCode = 0;
    printf("Enter an expression that is in a postfix form: ");
    char expression[MAX] = {'\0'};
    fgets(expression, sizeof(expression), stdin);
    int result = calculator(expression, &errorCode);
    (errorCode < 0) ? printf("Error\n") : printf("The result is %d", result);
}

bool operation(char operand, Stack **postfixMachine)
{
    ErrorCode errorCode = ok;
    int topElement = pop(postfixMachine, &errorCode);
    int deeperElement = pop(postfixMachine, &errorCode);
    if (errorCode < 0)
    {
        return false;
    }

    switch (operand)
    {
    case '-':
    {
        int tempResult = deeperElement - topElement;
        push(postfixMachine, tempResult);
        break;
    }
    case '+':
    {
        int tempResult = deeperElement + topElement;
        push(postfixMachine, tempResult);
        break;
    }
    case '*':
    {
        int tempResult = deeperElement * topElement;
        push(postfixMachine, tempResult);
        break;
    }
    case '/':
    {
        int tempResult = deeperElement / topElement;
        push(postfixMachine, tempResult);
        break;
    }
    }
    return true;
}

int calculator(char expression[], ErrorCode *errorCode)
{
    Stack *stack = NULL;
    int length = strlen(expression);
    for (int i = 0; i < length; ++i)
    {
        switch (expression[i])
        {
        case ' ':
        {
            break;
        }
        case '/':
        {
            operation(expression[i], &stack);
            break;
        }
        case '*':
        {
            operation(expression[i], &stack);
            break;
        }
        case '+':
        {
            operation(expression[i], &stack);
            break;
        }
        case '-':
        {
            operation(expression[i], &stack);
            break;
        }
        default:
        {
            ErrorCode errorCode = ok;
            push(&stack, expression[i] - '0');
            break;
        }
        }
    }
    int errorCodePeek = 0;
    int result = peek(stack);
    if (errorCodePeek < 0 || stack->previous != NULL)
    {
        *errorCode = -1;
    }
    return result;
}

bool tests()
{
    int errorCode = 0;
    char testExpression1[] = "9 6 - 1 2 + *";
    if (calculator(testExpression1, &errorCode) != 9)
    {
        printf("Failed on the example exrepssion\n");
        return false;
    }

    char testExpression2[] = "9 9 +";
    if (calculator(testExpression2, &errorCode) != 18)
    {
        printf("Addition fail\n");
        return false;
    }

    char testExpression3[] = "5 9 -";
    if (calculator(testExpression3, &errorCode) != -4)
    {
        printf("Subtraction fail\n");
        return false;
    }

    char testExpression4[] = "7 9 *";
    if (calculator(testExpression4, &errorCode) != 63)
    {
        printf("Multiplication fail\n");
        return false;
    }

    char testExpression5[] = "9 3 /";
    if (calculator(testExpression5, &errorCode) != 3)
    {
        printf("Devision fail\n");
        return false;
    }
    return true;
}