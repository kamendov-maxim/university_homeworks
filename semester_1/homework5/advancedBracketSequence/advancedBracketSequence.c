#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#include "../stack/stack.h"

// #include "tests/test1.txt"
// #include "tests/test2.txt"
// #include "tests/test3.txt"
// #include "tests/answer1.txt"
// #include "tests/answer2.txt"
// #include "tests/answer3.txt"

#define MAX 100

typedef enum ErrorCode
{
    OK,
    problemWithStack,
    incorrectInput
} ErrorCode;

bool isBalanced(const char *line, ErrorCode *errorCode, StackErrorCode *stackErrorCode);
bool inputCheck(char array[], size_t size, const char character);
char oppositeBracket(char bracket);

bool test(void);
bool testCheck(int tests[], int answers[]);

int main(void)
{
    if (!test())
    {
        printf("Простите, но похоже, что программа сейчас не работает корректно\n");
        return 1;
    }

    setlocale(LC_ALL, "Rus");

    printf("Введите вашу скобочную последовательность:\n");
    char line[MAX] = {'\0'};
    fgets(line, sizeof(line), stdin);

    // FILE *mf = fopen("test.txt", "r");
    // fgets(line, sizeof(line), mf);
    printf("Ваша скобочная последовательность: %s\n", line);

    ErrorCode errorCode = incorrectInput;
    StackErrorCode stackErrorCode = ok;

    bool check = isBalanced(line, &errorCode, &stackErrorCode);

    while (errorCode == incorrectInput)
    {
        printf("Последовательность должна состоять только из следующих символов: (, ), {, }, [, ]\n");
        printf("Попробуйте еще раз\n\n");

        printf("Введите вашу скобочную последовательность:\n");
        char line[MAX] = {'\0'};
        fgets(line, MAX, stdin);
        printf("Ваша скобочная последовательность: %s\n", line);
        check = isBalanced(line, &errorCode, &stackErrorCode);
    }

    // расписать ошибки, написать тесты

    if (errorCode != OK || stackErrorCode != ok)
    {
        printf("Похоже, что-то пошло не так\n");
        return 1;
    }

    if (check)
    {
        printf("Ваша скобочная последовательность сбалансирована\n");
        return 0;
    }
    printf("Ваша скобочная последовательность несбалансирована\n\n");

    return 0;
}

bool isBalanced(const char *line, ErrorCode *errorCode, StackErrorCode *stackErrorCode)
{
    char allowedCharacters[8] = {'(', '{', '[', ']', '}', ')', ' '};
    int i = 0;
    char currentBracket = line[i];
    StackErrorCode tempStackErrorCode = ok;
    Stack *stack = createStack(&tempStackErrorCode);

    if (tempStackErrorCode != ok)
    {
        *errorCode = problemWithStack;
        *stackErrorCode = tempStackErrorCode;
        deleteStack(stack);
        return false;
    }

    while (currentBracket != '\n' && currentBracket != '\0')
    {
        if (!inputCheck(allowedCharacters, 7, currentBracket))
        {
            *errorCode = incorrectInput;
            *stackErrorCode = tempStackErrorCode;
            deleteStack(stack);
            return false;
        }

        if (currentBracket == '(' || currentBracket == '{' || currentBracket == '[')
        {
            tempStackErrorCode = push(&stack, currentBracket);
            if (tempStackErrorCode != ok)
            {
                *errorCode = problemWithStack;
                *stackErrorCode = tempStackErrorCode;
                deleteStack(stack);
                return false;
            }
        }

        if (currentBracket == ')' || currentBracket == '}' || currentBracket == ']')
        {
            if (oppositeBracket(pop(&stack, &tempStackErrorCode)) != currentBracket)
            {
                if (tempStackErrorCode != ok)
                {
                    *errorCode = problemWithStack;
                    *stackErrorCode = tempStackErrorCode;
                    deleteStack(stack);
                    return false;
                }
                *errorCode = OK;
                *stackErrorCode = ok;
                deleteStack(stack);
                return false;
            }
        }
        ++i;
        currentBracket = line[i];
    }
    if (!isEmpty(stack))
    {
        printStack(stack);
        deleteStack(stack);
        *errorCode = OK;
        deleteStack(stack);
        *stackErrorCode = ok;
        return false;
    }
    deleteStack(stack);
    *errorCode = OK;
    *stackErrorCode = ok;
    return true;
}

bool inputCheck(char array[], size_t size, const char character)
{
    bool ans = false;
    for (int i = 0; i < size; ++i)
    {
        if (character == array[i])
        {
            ans = true;
        }
    }
    return ans;
}

char oppositeBracket(char bracket)
{
    switch (bracket)
    {
    case ('('):
    {
        return ')';
    }

    case ('{'):
    {
        return '}';
    }

    case ('['):
    {
        return ']';
    }
    }
    return '\0';
}



bool testCheck(int tests[], int answers[])
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
    ErrorCode errorCode = incorrectInput;
    StackErrorCode stackErrorCode = ok;
    bool testResult = isBalanced(line, &errorCode, &stackErrorCode);
    int tests[3] = {testResult, errorCode, stackErrorCode};
    return testCheck(tests, answers);
}

bool testCase2(void)
{
    char line[16] = "((]{})";
    int answers[3] = {0, 0, 0};
    ErrorCode errorCode = incorrectInput;
    StackErrorCode stackErrorCode = ok;
    bool testResult = isBalanced(line, &errorCode, &stackErrorCode);
    int tests[3] = {testResult, errorCode, stackErrorCode};
    return testCheck(tests, answers);
}

bool testCase3(void)
{
    char line[16] = "{a}";
    int answers[3] = {0, 2, 0};
    ErrorCode errorCode = incorrectInput;
    StackErrorCode stackErrorCode = ok;
    bool testResult = isBalanced(line, &errorCode, &stackErrorCode);
    int tests[3] = {testResult, errorCode, stackErrorCode};
    return testCheck(tests, answers);
}

bool test(void)
{
    return (testCase1() && testCase2() && testCase3());
}
