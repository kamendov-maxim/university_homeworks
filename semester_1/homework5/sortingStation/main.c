#include <stdio.h>
#include <locale.h>

#include "sortingStation/sortingStation.h"
#include "getString/getString.h"
#include "tests/test.h"

typedef enum ExitCode
{
    programFinishedCorrectly,
    programFailedTests,
    memoryError

} ExitCode;

int main(void)
{
    setlocale(LC_ALL, "Russian");

    if (test())
    {
        printf("К сожалению, программа сейчас не работает\n");
        return programFailedTests;
    }
    
    printf("Введите арифметическое выражение в инфиксной форме: ");
    char * expression = getString(stdin, '\n');
    if (expression == NULL)
    {
        printf("\nНедостаточно памяти\n");
        return memoryError;
    }
    
    printf("\nВыражение в постфиксной форме: ");
    char * ex = createPostfixForm(expression);
    printf("%s\n", ex);
    return programFinishedCorrectly;
}
