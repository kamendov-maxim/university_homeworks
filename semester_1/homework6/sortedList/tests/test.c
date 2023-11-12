#include <stdbool.h>

#include "test.h"
#include "../list/list.h"

#define SIZES_ARRAY_SIZE 3

static bool testCase(const int *testArray, const int *referenceArray, const int *popTestArray, const size_t *sizesArray)
{
    size_t testArraySize = sizesArray[0];
    size_t popArraySize = sizesArray[1];
    size_t referenceArraySize = sizesArray[2];
    List *list = createList();
    for (size_t i = 0; i < testArraySize; ++i)
    {
        if (append(list, testArray[i]) != ok)
        {
            return false;
        }
    }
    for (size_t i = 0; i < popArraySize; ++i)
    {
        if (pop(list, popTestArray[i]) != ok)
        {
            return false;
        }
    }

    return compareListWithArray(list, referenceArray, referenceArraySize);
}

bool test(void)
{
    const int testArray1[7] = {7, 4, 9, 1, 15, 65, 34};
    const int popTestArray1[3] = {4, 65, 15};
    const int referenceArray1[4] = {1, 7, 9, 34};
    const size_t sizesTestArray1[SIZES_ARRAY_SIZE] = {7, 3, 4};
    bool testCase1 = testCase(testArray1, referenceArray1, popTestArray1, sizesTestArray1);

    const int testArray2[5] = {5, 4, 3, 2, 1};
    const int popTestArray2[0] = {};
    const int referenceArray2[5] = {1, 2, 3, 4, 5};
    const size_t sizesTestArray2[SIZES_ARRAY_SIZE] = {5, 0, 5};
    bool testCase2 = testCase(testArray2, referenceArray2, popTestArray2, sizesTestArray2);

    const int testArray3[6] = {1, 2, 3, 4, 5, 6};
    const int popTestArray3[0] = {};
    const int referenceArray3[6] = {1, 2, 3, 4, 5, 6};
    const size_t sizesTestArray3[SIZES_ARRAY_SIZE] = {6, 0, 6};
    bool testCase3 = testCase(testArray3, referenceArray3, popTestArray3, sizesTestArray3);

    const int testArray4[5] = {1, 1, 1, 1, 1};
    const int popTestArray4[1] = {1};
    const int referenceArray4[4] = {1, 1, 1, 1};
    const size_t sizesTestArray4[SIZES_ARRAY_SIZE] = {5, 1, 4};
    bool testCase4 = testCase(testArray4, referenceArray4, popTestArray4, sizesTestArray4);

    const int testArray5[12] = {2, 2, 2, 3, 8, 1, 5, 6, 7, 3, 9, 5};
    const int popTestArray5[5] = {3, 5, 9, 2, 2};
    const int referenceArray5[7] = {1, 2, 3, 5, 6, 7, 8};
    const size_t sizesTestArray5[SIZES_ARRAY_SIZE] = {12, 5, 7};
    bool testCase5 = testCase(testArray5, referenceArray5, popTestArray5, sizesTestArray5);

    return testCase1 && testCase2 && testCase3 && testCase4;
}
