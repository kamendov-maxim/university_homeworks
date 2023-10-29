#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#include "../stack/stack.h"

#define MAX 100
#define PROGRAMFINISHEDCORRECTLY 0;
#define PROGRAMFINISHEDWITHERROR 1;
#define PROGRAMFAILEDTESTS 2;

typedef enum ErrorCode
{
    OK,
    PROBLEMWITHSTACK,
    INCORRECTINPUT
} ErrorCode;

bool isBalanced(const char *const line, ErrorCode *const errorCode);
char oppositeBracket(char bracket);
char *get_string(int *len);

bool test(void);
bool testCheck(const int *const tests, const int *const answers);

int main(void)
{
    if (!test())
    {
        printf("Простите, но похоже, что программа сейчас не работает корректно\n");
        return PROGRAMFAILEDTESTS;
    }

    setlocale(LC_ALL, "Rus");

    printf("Введите вашу скобочную последовательность:\n");

    int len = 0;
    char *line = get_string(&len);

    printf("Ваша скобочная последовательность: %s\n", line);

    ErrorCode errorCode = OK;

    bool check = isBalanced(line, &errorCode);

    if (errorCode != OK)
    {
        printf("Похоже, что-то пошло не так\n");
        return PROGRAMFINISHEDWITHERROR;
    }

    if (check)
    {
        printf("Ваша скобочная последовательность сбалансирована\n");
    }
    else
    {
        printf("Ваша скобочная последовательность несбалансирована\n\n");
    }

    return PROGRAMFINISHEDCORRECTLY;
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

char *get_string(int *len)
{
    *len = 0;
    int capacity = 1;
    char *s = (char *)malloc(sizeof(char));

    char c = getchar();

    while (c != '\n')
    {
        s[(*len)++] = c;

        if (*len >= capacity)
        {
            capacity *= 2;
            s = (char *)realloc(s, capacity * sizeof(char));
        }

        c = getchar();
    }

    s[*len] = '\0';

    return s;
}

bool testCheck(const int *const tests, const int *const answers)
{
    for (int i = 0; i < 3; ++i)
    {
        if (tests[i] != answers[i])
        {
            return false;
        }
    }

    return true;
}

bool testCase1(void)
{
    char line[16] = "(({[]()})[])[]{}";
    int answers[3] = {1, 0, 0};
    ErrorCode errorCode = INCORRECTINPUT;
    StackErrorCode stackErrorCode = ok;
    bool testResult = isBalanced(line, &errorCode);
    int tests[3] = {testResult, errorCode, stackErrorCode};
    return testCheck(tests, answers);
}

bool testCase2(void)
{
    char line[16] = "((]{})";
    int answers[3] = {0, 0, 0};
    ErrorCode errorCode = INCORRECTINPUT;
    StackErrorCode stackErrorCode = ok;
    bool testResult = isBalanced(line, &errorCode);
    int tests[3] = {testResult, errorCode, stackErrorCode};
    return testCheck(tests, answers);
}

bool test(void)
{
    return testCase1() && testCase2();
}
