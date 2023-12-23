#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "calculator.h"

static ErrorCode operation(Stack *stack, const char operand, CalculatorErrorCode *const calculatorErrorCode)
{
    ErrorCode errorCode = okStack;
    float number2 = getElement(stack, &errorCode);
    if (errorCode != ok)
    {
        return errorCode;
    }
    float number1 = getElement(stack, &errorCode);
    if (errorCode != ok)
    {
        return errorCode;
    }

    float result = 0;

    switch (operand)
    {
    case '-':
    {
        result = number1 - number2;
        break;
    }
    case '+':
    {
        result = number1 + number2;
        break;
    }
    case '*':
    {
        result = number1 * number2;
        break;
    }
    case '/':
    {
        if (number2 == 0)
        {
            *calculatorErrorCode = zeroDivisionError;
            return okStack;
        }
        result = number1 / number2;
        break;
    }

    default:
        *calculatorErrorCode = wrongOperationError;
        return okStack;
        break;
    }

    return addElement(stack, result);
}

float calculator(const char *const expression, CalculatorErrorCode *const calculatorErrorCode)
{
    Stack *stack = createStack();
    if (stack == NULL)
    {
        *calculatorErrorCode = memoryError;
        return 0;
    }

    size_t length = strlen(expression);
    ErrorCode ec = okStack;
    for (size_t i = 0; i < length; ++i)
    {
        char currentCharacter = expression[i];
        if (currentCharacter != ' ')
        {
            if (isdigit(currentCharacter))
            {
                ec = addElement(stack, currentCharacter - '0');
                if (ec != ok)
                {
                    deleteStack(&stack);
                    *calculatorErrorCode = memoryError;
                    return 0;
                }
            }
            else
            {
                ec = operation(stack, currentCharacter, calculatorErrorCode);
                if (ec != okStack || *calculatorErrorCode != ok)
                {
                    deleteStack(&stack);
                    return 0;
                }
            }
        }
    }

    float answer = getElement(stack, &ec);
    deleteStack(&stack);
    if (ec != okStack)
    {
        *calculatorErrorCode = algorithmWorkError;
        return 0;
    }
    *calculatorErrorCode = ok;

    return answer;
}
