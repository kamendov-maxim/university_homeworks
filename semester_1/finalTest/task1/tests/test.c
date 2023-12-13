#include <string.h>
#include <stdlib.h>

#include "test.h"
#include "../getMinimalNumber/getMinimalNumber.h"

static const bool testCase(char const *const input, char const *const answer)
{
    char *newNumber = getMinimalNumber(input);
    if (newNumber == NULL)
    {
        return false;
    }
    bool result = strcmp(newNumber, answer) == 0;
     free(newNumber);
    return result;
}

const bool test(void)
{
    const char * const input1 = "564353456";
    const char * const answer1 = "334455566";
    const char * const input2 = "5435";
    const char * const answer2 = "3455";

    return testCase(input1, answer1) && testCase(input2, answer2);
}