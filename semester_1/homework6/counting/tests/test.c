#include <stdbool.h>

#include "test.h"
#include "../list/list.h"

bool test(void)
{
    ListErrorCode listErrorCode = ok;

    int testN1 = 10;
    int testM1 = 3;
    int answer1 = 4;
    bool testCase1 = (count(testN1, testM1, &listErrorCode) == answer1);
    if (listErrorCode != ok)
    {
        return false;
    }

    int testN2 = 6;
    int testM2 = 2;
    int answer2 = 5;
    bool testCase2 = (count(testN2, testM2, &listErrorCode) == answer2);

    int testN3 = 6;
    int testM3 = 5;
    int answer3 = 1;
    bool testCase3 = (count(testN3, testM3, &listErrorCode) == answer3);
    if (listErrorCode != ok)
    {
        return false;
    }

    return testCase1 && testCase2 && testCase3;
}
