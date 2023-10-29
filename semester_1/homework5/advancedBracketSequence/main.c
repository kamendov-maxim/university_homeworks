#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#include "advancedBracketSequence.h"
#include "test/test.h"

#define PROGRAMFINISHEDCORRECTLY 0;
#define PROGRAMFINISHEDWITHERROR 1;
#define PROGRAMFAILEDTESTS 2;

char *get_string(int *len);

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
