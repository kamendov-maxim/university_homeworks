#include <stdbool.h>

#include "test.h"
#include "../list/list.h"

static bool testCase(const int * testArray, const size_t size)
{
    ListErrorCode listErrorCode = ok;
    List *list = createList(&listErrorCode);
    for (size_t i = 0; i < size; ++i)
    {
        listErrorCode = append(list, testArray[i]);
        if (listErrorCode != ok)
        {
            return false;
        }
    }

    return isSorted(list);
}

bool test(void)
{
    const int testArray1[7] = {7, 4, 9, 1, 15, 65, 34};
    bool testCase1 = testCase(testArray1, 7);

    const int testArray2[5] = {5, 4, 3, 2, 1};
    bool testCase2 = testCase(testArray2, 5);

    const int testArray3[6] = {1, 2, 3, 4, 5, 6};
    bool testCase3 = testCase(testArray3, 6);
     
    const int testArray4[5] = {1, 1, 1, 1, 1};
    bool testCase4 = testCase(testArray4, 5);

    return testCase1 && testCase2 && testCase3 && testCase4;
}