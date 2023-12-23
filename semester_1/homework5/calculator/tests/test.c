#include <stdlib.h>

#include <stdio.h>

#include "test.h"
#include "../calculator/calculator.h"

static const bool testCase(char const *const expression, const float answer)
{
    CalculatorErrorCode errorCode = ok;
    if (calculator(expression, &errorCode) != answer || errorCode != ok)
    {
        return false;
    }
    return true;
}

const bool test(void)
{
    size_t const testNumber = 5;
    char const *const expresions[testNumber] = {"9 6 - 1 2 + *", "3 4 * 1 + 4 -", "9 2 /", " 5 5 * 5 * 5 * 5 *", " 2 2 /"};
    const float answers[testNumber] = {9, 9, 4.5, 3125, 1};
    for (size_t i = 0; i < testNumber; ++i)
    {
        if (!testCase(expresions[i], answers[i]))
        {
            printf("%d\n", i);
            return false;
        }
    }
    return true;
}
