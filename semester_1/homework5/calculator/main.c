#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "String/String.h"
#include "calculator/calculator.h"
#include "tests/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define RUNTIME_ERROR 3
#define WRONG_INPUT 4

int main(void)
{
    setlocale(LC_ALL, "Russian");

    if (!test())
    {
        printf("Программа сейчас не работает\n");
        return PROGRAM_FAILED_TESTS;
    }
    
    size_t len = 0;
    printf("Введите выражение в постфиксной форме: ");
    char * input = getString(&len, stdin, '\n');
    if (input == NULL)
    {
        printf("Ошибка\n");
        return MEMORY_ERROR;
    }

    CalculatorErrorCode calculatorErrorCode = ok;
    float answer = calculator(input, &calculatorErrorCode);
    free(input);
    if (calculatorErrorCode == zeroDivisionError)
    {
        printf("Нельзя делить на ноль\n");
        return WRONG_INPUT;
    }
    else if (calculatorErrorCode == wrongOperationError)
    {
        printf("Неправильная операция\n");
        return WRONG_INPUT;
    }
    
    if (calculatorErrorCode != ok)
    {
        printf("Ошибка\n");
        return (calculatorErrorCode == memoryError? MEMORY_ERROR : RUNTIME_ERROR);
    }

    printf("Результат: %f\n", answer);
}
