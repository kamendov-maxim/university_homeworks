#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../Stack/Stack.h"
#include "sortingStation.h"

static void ignoreSpaces(char const *const expression, size_t *const counter)
{
    for (; expression[*counter] == ' '; ++(*counter))
        ;
}

static int compareOperators(char const operator1, char const operator2)
{
    if (operator1 == '*' || operator1 == '/')
    {
        if (operator2 == '+' || operator2 == '-')
        {
            return 1;
        }
        return 0;
    }
    else
    {
        if (operator2 == '+' || operator2 == '-')
        {
            return 0;
        }
        return -1;
    }
}

static StackErrorCode moveToOutputStack(Stack *const outputStack, Stack *const operatorsStack)
{
    StackErrorCode ec = okStack;
    for (char currentOperator = getElement(operatorsStack, &ec);
         currentOperator != '(' && ec != emptyStack; currentOperator = getElement(operatorsStack, &ec))
    {
        StackErrorCode ec2 = addElement(outputStack, currentOperator);
        if (ec2 != okStack)
        {
            return ec2;
        }
    }
    return okStack;
}

char *createPostfixForm(char const *const infixForm)
{
    size_t len = strlen(infixForm);
    size_t counter = 0;

    Stack *outputStack = createStack();
    if (outputStack == NULL)
    {
        return NULL;
    }
    Stack *operatorsStack = createStack();
    if (operatorsStack == NULL)
    {
        deleteStack(&outputStack);
        return NULL;
    }

    StackErrorCode ec = okStack;

    for (size_t i = 0; i < len; ++i)
    {
        ignoreSpaces(infixForm, &i);
        if (i >= len)
        {
            break;
        }
        char currentChar = infixForm[i];
        if (isdigit(currentChar))
        {
            ec = addElement(outputStack, infixForm[i]);
        }
        else if (currentChar == ')')
        {
            ec = moveToOutputStack(outputStack, operatorsStack);
        }
        else if (currentChar == '(')
        {
            ec = addElement(operatorsStack, currentChar);
        }
        else
        {
            char top = topElement(operatorsStack, &ec);
            int comparison = compareOperators(top, currentChar);
            while (ec != emptyStack && top != '(' && comparison != -1)
            {
                char operatorFromStack = getElement(operatorsStack, &ec);
                ec = addElement(outputStack, operatorFromStack);
                top = topElement(operatorsStack, &ec);
                comparison = compareOperators(top, currentChar);
            }
            ec = addElement(operatorsStack, currentChar);
        }
        if (ec != okStack)
        {
            deleteStack(&operatorsStack);
            deleteStack(&outputStack);
            return NULL;
        }
    }
    ec = moveToOutputStack(outputStack, operatorsStack);
    char *output = createString(outputStack, &ec);
    deleteStack(&operatorsStack);
    deleteStack(&outputStack);
    return output;
}
