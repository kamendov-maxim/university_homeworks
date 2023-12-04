#include <stdlib.h>

#include "test.h"

static const bool compareArrays(int const *const testArray, int const * const answerArray, size_t const size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (testArray[i] != answerArray[i])
        {
            return false;
        }
    }
    return true;
}

static const bool testSmartQuickSortFunction(void)
{
    int testArray1[5] = {5, 4, 3, 2, 1};
    int answerArray1[5] = {1, 2, 3, 4, 5};
    const size_t size1 = 5;

    int testArray2[5] = {1, 2, 3, 4, 5};
    int answerArray2[5] = {1, 2, 3, 4, 5};
    const size_t size2 = 5;

    int testArray3[1] = {1};
    int answerArray3[1] = {1};
    const size_t size3 = 1;

    smartQuickSort(testArray1, 0, size1 - 1);

    smartQuickSort(testArray2, 0, size2 - 1);

    smartQuickSort(testArray3, 0, size3 - 1);

    return compareArrays(testArray1, answerArray1, 5) && compareArrays(testArray2, answerArray2, 5) && compareArrays(testArray3, answerArray3, 1);
}

const bool testSmartQuickSort(void)
{
    int testArray1[5] = {5, 4, 3, 2, 1};
    int answerArray1[5] = {1, 2, 3, 4, 5};
    const size_t size1 = 5;

    int testArray2[5] = {1, 2, 3, 4, 5};
    int answerArray2[5] = {1, 2, 3, 4, 5};
    const size_t size2 = 5;

    int testArray3[1] = {1};
    int answerArray3[1] = {1};
    const size_t size3 = 1;

    smartQuickSort(testArray1, 0, size1 - 1);

    smartQuickSort(testArray2, 0, size2 - 1);

    smartQuickSort(testArray3, 0, size3 - 1);

    return compareArrays(testArray1, answerArray1, 5) && compareArrays(testArray2, answerArray2, 5) && compareArrays(testArray3, answerArray3, 1);
    // return testSwapFunction() && testPartitionFunction() && testSmartQuickSortFunction();
}