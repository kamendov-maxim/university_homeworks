#include <stdlib.h>
#include <locale.h>

#include "../stack/stack.h"
#include "advancedBracketSequence.h"

bool test(void);
bool testCheck(const int *const tests, const int *const answers);

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
    int i = 0;
    char currentBracket = line[i];
    StackErrorCode stackErrorCode = ok;
    Stack *stack = NULL;

    while (currentBracket != '\n' && currentBracket != '\0')
    {

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

        if (currentBracket == ')' || currentBracket == '}' || currentBracket == ']')
        {
            bool check = oppositeBracket(top(stack, &stackErrorCode)) == currentBracket;

            if (stackErrorCode != ok)
            {
                *errorCode = PROBLEMWITHSTACK;
                deleteStack(&stack);
                return false;
            }

            stackErrorCode = pop(&stack);
            if (stackErrorCode != ok)
            {
                *errorCode = PROBLEMWITHSTACK;
                deleteStack(&stack);
                return false;
            }

            if (!check)
            {
                *errorCode = OK;
                deleteStack(&stack);
                return false;
            }
        }
        ++i;
        currentBracket = line[i];
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
