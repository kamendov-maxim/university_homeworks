#include <stdbool.h>

#include "test.h"
#include "../listMergeSort/list.h"


// bool test(void)
// {
//     return true;
// }

static bool testCase(char  * const names[], char  * const numbers[], size_t sizeOfArray)
{
    ListErrorCode testListErrorCode = ok;
    List *testList = createList(&testListErrorCode);
    if (testListErrorCode != ok)
    {
        return false;
    }

    for (int i = 0; i < sizeOfArray; ++i)
    {
        testListErrorCode = append(testList, names[i], numbers[i]);
        if (testListErrorCode != ok)
        {
            return false;
        }
    }

    mergeSortByNumber(testList);
    if (!isSortedByNumber(testList))
    {
        deleteList(testList);
        return false;
    }

    mergeSortByName(testList);
    if (!isSortedByName(testList))
    {
        deleteList(testList);
        return false;
    }

    deleteList(testList);

    return true;
}

bool test(void)
{
    char  * const testNames1[5] = {"bbb", "aaa", "ccc", "eee", "ddd"};
    char  * const testNumbers1[5] = {"3", "2", "5", "4", "1"};
    bool testCase1 = testCase(testNames1, testNumbers1, 5);

    char  * const testNames2[5] = {"eee", "ddd", "ccc", "bbb", "aaa"};
    char  * const testNumbers2[5] = {"5", "4", "3", "2", "1"};
    bool testCase2 = testCase(testNames2, testNumbers2, 5);

    char  * const testNames3[5] = {"aaa", "aaa", "aaa", "aaa", "aaa"};
    char  * const testNumbers3[5] = {"1", "1", "1", "1", "1"};
    bool testCase3 = testCase(testNames3, testNumbers3, 5);

    return testCase1 && testCase2 && testCase3;
}
