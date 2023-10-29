#include <stdlib.h>
#include <locale.h>

#include "../stack/stack.h"
#include "advancedBracketSequence.h"

char oppositeBracket(char bracket)
{
    switch (bracket)
    {
    case '(':
        return ')';

    case '{':
        return '}';

    case '[':
        return ']';
    }
    return '\0';
}

bool isBalanced(const char *const line, ErrorCode *const errorCode)
{
    StackErrorCode stackErrorCode = ok;
    Stack *stack = NULL;

    for (size_t i = 0; line[i] != '\n' && line[i] != '\0'; ++i)
    {
        char currentBracket = line[i];

        if (currentBracket == '(' || currentBracket == '{' || currentBracket == '[')
        {
            stackErrorCode = push(&stack, currentBracket);
            if (stackErrorCode != ok)
            {
                *errorCode = PROBLEMWITHSTACK;
                deleteStack(&stack);
                return false;
            }
        }
        else if (currentBracket == ')' || currentBracket == '}' || currentBracket == ']')
        {
            char topElement = top(stack, &stackErrorCode);

            if (stackErrorCode != ok)
            {
                *errorCode = PROBLEMWITHSTACK;
                deleteStack(&stack);
                return false;
            }

            pop(&stack);

            const bool check = (oppositeBracket(topElement) == currentBracket);

            if (!check)
            {
                *errorCode = OK;
                deleteStack(&stack);
                return false;
            }
        }
    }

    if (!isEmpty(stack))
    {
        printStack(stack);
        deleteStack(&stack);
        *errorCode = OK;
        deleteStack(&stack);
        return false;
    }
    deleteStack(&stack);
    *errorCode = OK;
    return true;
}
