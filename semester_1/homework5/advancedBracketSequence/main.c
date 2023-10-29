#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#include "advancedBracketSequence.h"
#include "test/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0;
#define PROGRAM_FINISHED_WITH_ERROR 1;
#define PROGRAM_FAILED_TESTS 2;
#define MEMORY_ERROR 3;

static char *get_string(size_t * const len);

int main(void)
{
    if (!test())
    {
        printf("Простите, но похоже, что программа сейчас не работает корректно\n");
        return PROGRAM_FAILED_TESTS;
    }

    setlocale(LC_ALL, "Rus");

    printf("Введите вашу скобочную последовательность:\n");

    size_t len = 0;
    char *line = get_string(&len);

    if (line == NULL)
    {
        printf("Ошибка доступа к памяти\n");
        return MEMORY_ERROR;
    }


    ErrorCode errorCode = OK;

    const bool check = isBalanced(line, &errorCode);

    if (errorCode != OK)
    {
        printf("Похоже, что-то пошло не так\n");
        return PROGRAM_FINISHED_WITH_ERROR;
    }

    if (check)
    {
        printf("Ваша скобочная последовательность сбалансирована\n\n");
    }
    else
    {
        printf("Ваша скобочная последовательность несбалансирована\n\n");
    }

    return PROGRAM_FINISHED_CORRECTLY;
}

static char *get_string(size_t * const len)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));

    for (char c = getchar(); c != '\n'; c = getchar())
    {
        s[(*len)++] = c;

        if (*len >= capacity)
        {
            capacity *= 2;
            s = (char *)realloc(s, capacity * sizeof(char));
            if (s == NULL)
            {
                *len = 0;
                return NULL;
            }
        }
    }

    s[*len] = '\0';

    return s;
}
