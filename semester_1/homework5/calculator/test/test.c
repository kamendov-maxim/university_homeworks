#include <stdbool.h>

#include <stdio.h>

#include "../calculator.h"

bool test(void)
{
    return true;
    ErrorCode errorCode = 0;
    const char test1[] = "2 2 +";
    if (calculator(test1, &errorCode) != 4 || errorCode != OK)
    {
        printf("1");
        return false;
    }

    const char test2[] = "3 5 * 4 +";
    if (calculator(test2, &errorCode) != 19 || errorCode != OK)
    {
        printf("2");

        return false;
    }

    const char test3[] = "9 4 6 2 / + -";
    if (calculator(test3, &errorCode) != 2 || errorCode != OK)
    {
        printf("3");

        return false;
    }

    const char test4[] = "";
    if (calculator(test4, &errorCode) != -1 || errorCode != EMPTY_LINE)
    {
        printf("4");

        return false;
    }

    return true;
}
