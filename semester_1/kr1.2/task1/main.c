#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "compareBinaryNumbers/compareBinaryNumbers.h"
#include "tests/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1

static void printBinaryNumber(const bool *const number, const size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        printf("%d", number[i]);
    }
    printf("\n");
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    if (!test())
    {
        printf("Программа сейчас не работает\n");
        return PROGRAM_FAILED_TESTS;
    }
    
    const size_t len1 = 6;
    const size_t len2 = 8;
    const bool number1[len1] = {false, true, false, false, true, true};
    const bool number2[len2] = {false, false, false, false, true, true, false, true};
    printf("Числа:\n");
    printf("Первое число: ");
    printBinaryNumber(number1, len1);
    printf("Второе число: ");
    printBinaryNumber(number2, len2);
    int answer = compare(number1, len1, number2, len2);
    if (answer > 0)
    {
        printf("Первое число больше второго\n");
    }
    else if (answer < 0)
    {
        printf("Второе число больше первого\n");
    }
    else
    {
        printf("Числа равны");
    }

    return PROGRAM_FINISHED_CORRECTLY;
}
