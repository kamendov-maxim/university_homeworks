#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../sortingStation/sortingStation.h"

const bool test(void)
{
    const size_t testNumber = 6;
    const char * const testExpressions[testNumber] = {
        "1 + 2",
        " ( 2 + 4) * 5",
        " 2 +    4 *  5 ",
        " 4 * 6 * 7 * 8",
        "(1 + (2 - 3) + (7 / 2)) * (1 + 8)",
        "1"
        };
    
    const char * const answers[testNumber] = {
        "1 2 +",
        "2 4 + 5 *",
        "2 4 5 * +",
        "4 6 * 7 * 8 *",
        "1 2 3 - 7 2 / + 1 8 + 8"
    };

    for (size_t i = 0; i < testNumber; ++i)
    {
        char * expression = createPostfixForm(testExpressions[i]);
        if (expression == NULL)
        {
            return false;
        }
        int comparison = strcmp(expression, answers[i]);
        free(expression);
        if (comparison != 0)
        {
            return false;
        }    
    }
    return true;
}
