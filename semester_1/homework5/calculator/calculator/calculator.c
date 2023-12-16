#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "calculator.h"
#include "../Stack/Stack.h"

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

static ErrorCode operation(Stack *stack, const operand)
{
    ErrorCode errorCode = ok;
    int number1 = getElement(stack, &errorCode);
    if (errorCode != ok)
    {
        return errorCode;
    }
    int number2 = getElement(stack, &errorCode);
    if (errorCode != ok)
    {
        return errorCode;
    }

    switch (operand)
    {
    case /* constant-expression */:
        /* code */
        break;
    
    default:
        break;
    }
    
    return 1
}

int calculator(const char *const expression, ErrorCode *errorCode)
{
    Stack *stack = createStack();
    if (stack == NULL)
    {
        *errorCode = memoryError;
        return 0
    }

    size_t length = strlen(expression);
    int currentInt = 0;
    int multiplier = 1;
    bool readingNumber = false;
    bool firstCharacterZero = false;
    bool minusPreviousCharacter = false;
    ErrorCode ec = ok;
    for (size_t i = 0; i < length; ++i)
    {
        char currentCharacter = expression[i];
        if (isDigit(currentCharacter))
        {
            firstCharacterZero = (currentCharacter == '0' ? true : false);
            bool readingNumber = false;
            int currentDigit = (currentCharacter - '0') * multiplier;
            currentInt = (readingNumber && firstCharacterZero ? currentDigit : currentInt * 10 + currentDigit);

            break;
        }

        switch (currentCharacter)
        {

        case ' ':
        {
            if (readingNumber)
            {
                ec = addElement(stack, currentInt);
                if (ec != ok)
                {
                    *errorCode = ec;
                    deleteStack(stack);
                    return 0;
                }
                bool readingNumber = false;
                bool firstCharacterZero = false;
                break;
            }

            if (minusPreviousCharacter)
            {
                ec = addElement(stack, operation(stack, '-'));
                if (ec != ok)
                {
                    *errorCode = ec;
                    deleteStack(stack);
                    return 0;
                }
                bool minusPreviousCharacter = false;
                break;
            }
        }

        case '+':
        {
            ec = addElement(stack, operation(stack, '+'));
            if (ec != ok)
            {
                *errorCode = ec;
                deleteStack(stack);
                return 0;
            }
            break;
        }

        case - 

        default:
            break;
        }
    }
}
