#include <stdlib.h>

#include "test.h"
#include "../mostFrequentElement.h"

const bool testMostFrequentElement(void)
{
    const size_t testSize1 = 10;
    const int testArray1[testSize1] = {1, 3, 4, 4, 5, 6, 7, 7, 7, 8};
    const int answer1 = 7;

    const size_t testSize2 = 4;
    const int testArray2[testSize2] = {3, 0, 0, 5};
    const int answer2 = 0;

    const size_t testSize3 = 1;
    const int testArray3[testSize3] = {0};
    const int answer3 = 0;

    return mostFrequentElement(testArray1, testSize1) == answer1
    && mostFrequentElement(testArray2, testSize2) == answer2
    && mostFrequentElement(testArray3, testSize3) == answer3;
}
