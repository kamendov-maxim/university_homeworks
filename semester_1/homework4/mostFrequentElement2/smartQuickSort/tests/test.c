#include <stdlib.h>
#include <string.h>

#include "test.h"

const bool testSmartQuickSort(void)
{
    const size_t testSize1 = 5;
    int testArray1[testSize1] = {5, 4, 3, 2, 1};
    int answerArray1[testSize1] = {1, 2, 3, 4, 5};

    const size_t testSize2 = 5;
    int testArray2[testSize2] = {1, 2, 3, 4, 5};
    int answerArray2[testSize2] = {1, 2, 3, 4, 5};

    const size_t testSize3 = 1;
    int testArray3[testSize3] = {1};
    int answerArray3[testSize3] = {1};

    smartQuickSort(testArray1, 0, testSize1 - 1);
    smartQuickSort(testArray2, 0, testSize2 - 1);
    smartQuickSort(testArray3, 0, testSize3 - 1);

    return memcmp(testArray1, answerArray1, testSize1) == 0
    && memcmp(testArray2, answerArray2, testSize2) == 0
    && memcmp(testArray3, answerArray3, testSize3) == 0;
}
