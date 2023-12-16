#include <stdio.h>


#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "calculator.h"

const char *const numbers = "0123456789";
const size_t numbersNumber = 10;

static const bool isDigit(const char character)
{
    for (size_t i = 0; i < numbersNumber; i++)
    {
        if (numbers[i] == character)
        {
            return true;
        }
    }
    return false;
}

static ErrorCode operation(Stack *stack, const char operand)
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
        result = number1 / number2;
        break;
    }

    default:
        break;
    }

    errorCode = addElement(stack, result);
    if (errorCode != ok)
    {
        return errorCode;
    }
    return errorCode;
}

float calculator(const char *const expression, CalculatorErrorCode *calculatorErrorCode)
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

        if (isDigit(currentCharacter))
        {
            ec = addElement(stack, currentCharacter - '0');
            if (ec != ok)
            {
                deleteStack(stack);
                *calculatorErrorCode = memoryError;
                return 0;
            }
        }


        switch (currentCharacter)
        {

        case '-':
        {
            ec = operation(stack, '-');
            if (ec != ok)
            {
                *calculatorErrorCode = algorithmWorkError;
                return 0;
            }
            break;
        }

        case '+':
        {
            ec = operation(stack, '+');
            if (ec != ok)
            {
                *calculatorErrorCode = algorithmWorkError;
                return 0;
            }
            break;
        }

        case '*':
        {
            ec = operation(stack, '*');
            if (ec != ok)
            {
                *calculatorErrorCode = algorithmWorkError;
                return 0;
            }
            break;
        }

        case '/':
        {
            ec = operation(stack, '/');
            if (ec != ok)
            {
                *calculatorErrorCode = algorithmWorkError;
                return 0;
            }
            break;
        }

        default:
            break;
        }
    }
    float answer = getElement(stack, &ec);
    if (ec != ok)
    {
        *calculatorErrorCode = algorithmWorkError;
        return 0;
    }
    *calculatorErrorCode = ok;

    return answer;
}
