#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "parseTree/parseTree.h"
#include "String/String.h"
#include "tests/test.h"

typedef enum exitCode
{
    ok,
    programFailedTests,
    memoryError,
    fileReadingError
} exitCode;

char const * const fileName = "../file.txt";

static char * readFile(char const * const fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Ошибка чтения файла\n");
        exit(fileReadingError);
    }
    char * expression = getString(file, EOF);
    fclose(file);
    if (expression == NULL)
    {
        printf("Кончилась память\n");
        exit(memoryError);
    }
    return expression;
}

exitCode main(void)
{
    setlocale(LC_ALL, "Russian");
    
    if (!test())
    {
        printf("Программа сейчас не рабоатет\n");
        return programFailedTests;
    }

    char * expression = readFile(fileName);
    ParseTree * parseTree = createTree(expression);
    free(expression);
    printf("Значение выражения из файла: %f\n", calculate(parseTree));
    deleteTree(&parseTree);
    return ok;
}
