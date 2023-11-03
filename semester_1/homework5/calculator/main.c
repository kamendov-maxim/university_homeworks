#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "../get_string/get_string.h"
#include "calculator.h"
#include "test/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define PROGRAM_FINISHED_WITH_ERROR 2
#define MEMORY_ACCESS_ERROR 3

int main()
{
    setlocale(LC_ALL, "Rus");
    if (!test())
    {
        printf("Простите, но похоже, что программа сейчас не работает корректно\n");
        return PROGRAM_FAILED_TESTS;
    }

    printf("Введите арифметическое выражение в постфиксной форме: ");

    size_t len = 0;
    char *expression = get_string(&len);
    if (expression == NULL)
    {
        printf("Ошибка доступа к памяти\n");
        return MEMORY_ACCESS_ERROR;
    }
    ErrorCode errorCode = OK;

    int result = calculator(expression, &errorCode);
    if (errorCode != OK)
    {
        printf("Похоже, что-то пошло не так\n");
        return PROGRAM_FINISHED_WITH_ERROR;
    }
    printf("Ответ: %d", result);

    return PROGRAM_FINISHED_CORRECTLY;
}
