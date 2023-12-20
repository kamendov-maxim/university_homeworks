#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

#include "checkString/checkString.h"
#include "getString/getString.h"
#include "tests/test.h"

typedef enum ExitCode
{
    ok,
    programFailedTests,
    memoryError
} ExitCode;

ExitCode main(void)
{
    setlocale(LC_ALL, "Russian");

    if (!test())
    {
        printf("Программа сейчас не работает\n");
        return programFailedTests;
    }

    printf("Введите строку, которую хотите проверить: ");
    char *input = getString(stdin, '\n');
    if (input == NULL)
    {
        return memoryError;
    }

    const char *const output = (checkString(input) ? "Автомат принял строку\n" : "Автомат не принял строку\n");
    printf("%s", output);
    free(input);

    return ok;
}
