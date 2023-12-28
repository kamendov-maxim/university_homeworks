#include <stdio.h>
#include <locale.h>

#include "findComments/findComments.h"
#include "tests/test.h"

#define FILENAME "../file.txt"

typedef enum exitCode
{
    programFinishedCorrectly,
    programFailedTests,
    notEnoughMemory
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
    char **comments = findComments(FILENAME, &len);
    if (comments == NULL)
    {
        printf("Недостаточно памяти\n");
        return notEnoughMemory;
    }
    
    printf("Комментарии из файла:\n");
    for (size_t i = 0; i < len; ++i)
    {
        printf("%s\n", comments[i]);
        free(comments[i]);
    }
    free(comments);
    return programFinishedCorrectly;
}
