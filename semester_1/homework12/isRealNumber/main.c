#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>

#include "../String/String.h"
#include "isRealNumber/isRealNumber.h"
#include "tests/test.h"

typedef enum exitCode
{
    programFinishedCorrectly,
    programFailedTests,
    memoryError
} exitCode;

int main(void)
{
    setlocale(LC_ALL, "Russian");

    if (!test())
    {
        printf("Программа сейчас не работает\n");
        return programFailedTests;
    }

    size_t len = 0;
    printf("Введите строку, которую хотите проверить: ");
    char *input = getString(&len, stdin, '\n');
    if (input == NULL)
    {
        printf("Ошибка\n");
        return memoryError;
    }

    char *reply = (isRealNumber(input) ? "Введенная строка является вещественным числом\n"
                                       : "Введенная строка не является вещественным числом\n");
    free(input);
    printf("%s", reply);

    return programFinishedCorrectly;
}
