#include "test.h"
#include "../advancedBracketSequence.h"

#define TEST_ARRAYS_SIZE 2

bool testCheck(const unsigned char *const tests, const unsigned char *const answers)
{
    for (int i = 0; i < TEST_ARRAYS_SIZE; ++i)
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
    const char line[16] = "(({[]()})[])[]{}";
    unsigned char answers[TEST_ARRAYS_SIZE] = {1, 0};
    ErrorCode errorCode = OK;
    const bool testResult = isBalanced(line, &errorCode);
    unsigned char tests[TEST_ARRAYS_SIZE] = {testResult, errorCode};
    return testCheck(tests, answers);
}

bool testCase2(void)
{
    const char line[16] = "((]{})";
    unsigned char answers[TEST_ARRAYS_SIZE] = {0, 0};
    ErrorCode errorCode = OK;
    const bool testResult = isBalanced(line, &errorCode);
    unsigned char tests[TEST_ARRAYS_SIZE] = {testResult, errorCode};
    return testCheck(tests, answers);
}

bool test(void)
{
    return testCase1() && testCase2();
}
