#include <stdio.h>
#include <locale.h>

#include "findComments/findComments.h"

#define FILENAME "../file.txt"

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

    }

    size_t len = 0;
    char **comments = findComments(FILENAME, &len);
    for (size_t i = 0; i < len; ++i)
    {
        printf("%s\n", comments[i]);
        free(comments[i]);
    }
    free(comments);
}
