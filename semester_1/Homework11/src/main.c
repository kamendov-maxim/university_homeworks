#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "../include/subString.h"
#include "../include/String.h"
#include "../include/readFile.h"
#include "../include/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define FILE_ERROR 3

#define FILE_NAME "../file.txt"

int main(void)
{
    setlocale(LC_ALL, "utf-8");

    if (!test())
    {
        printf("Программа сейчас не работает\n");
        return PROGRAM_FAILED_TESTS;
    }

    size_t len = 0;
    printf("Введите подстроку: ");
    char *pattern = getString(&len, stdin, '\n');
    if (pattern == NULL)
    {
        return MEMORY_ERROR;
    }
    char *text = readFile(FILE_NAME);
    if (text == NULL)
    {
        free(pattern);
        return MEMORY_ERROR;
    }

    ErrorCode errorCode = ok;
    long answer = findSubstring(pattern, text, &errorCode);
    free(text);

    if (errorCode != ok)
    {
        free(pattern);
        printf("Программа не может получить доступ к памяти\n");
        return MEMORY_ERROR;
    }

    if (answer == -1)
    {
        printf("Подстрока %s не встречается в тексте ни разу\n", pattern);
        free(pattern);
        return PROGRAM_FINISHED_CORRECTLY;
    }

    printf("Первое вхождение подстроки %s в тексте начинается на %ld символе\n", pattern, answer);
    free(pattern);
    return PROGRAM_FINISHED_CORRECTLY;
}
