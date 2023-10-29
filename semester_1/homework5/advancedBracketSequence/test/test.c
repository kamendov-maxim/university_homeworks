#include "test.h"
#include "../advancedBracketSequence.h"

bool testCheck(const int *const tests, const int *const answers)
{
    for (int i = 0; i < 3; ++i)
    {
        if (tests[i] != answers[i])
        {
            return false;
        }
    }

    return true;
}

bool testCase1(void)
{
    char line[16] = "(({[]()})[])[]{}";
    int answers[3] = {1, 0, 0};
    ErrorCode errorCode = OK;
    bool testResult = isBalanced(line, &errorCode);
    int tests[3] = {testResult, errorCode};
    return testCheck(tests, answers);
}

bool testCase2(void)
{
    char line[16] = "((]{})";
    int answers[3] = {0, 0, 0};
    ErrorCode errorCode = OK;
    bool testResult = isBalanced(line, &errorCode);
    int tests[3] = {testResult, errorCode};
    return testCheck(tests, answers);
}

bool test(void)
{
    return testCase1() && testCase2();
}
