#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "../compareBinaryNumbers/compareBinaryNumbers.h"

const bool testCase1(void)
{
    const size_t len1 = 5;
    const bool number1[len1] = {true, true, true, true, true};
    const size_t len2 = 3;
    const bool number2[5] = {true, true, true};
    return compare(number1, len1, number2, len2) == 1;
}

const bool testCase2(void)
{
    const size_t len1 = 5;
    const bool number1[len1] = {false, false, true, true, true};
    const size_t len2 = 3;
    const bool number2[len2] = {true, true, true};
    return compare(number1, len1, number2, len2) == 0;
}

const bool testCase3(void)
{
    const size_t len1 = 5;
    const bool number1[len1] = {false, false, false, false, false};
    const size_t len2 = 3;
    const bool number2[len2] = {true, true, true};
    return compare(number1, len1, number2, len2) == -1;
}

const bool testCase4(void)
{
    const size_t len1 = 4;
    const bool number1[len1] = {true, true, true, true};
    const size_t len2 = 6;
    const bool number2[len2] = {true, true, true, true, true, true};
    return compare(number1, len1, number2, len2) == -1;
}

const bool testCase5(void)
{
    const size_t len1 = 4;
    const bool number1[len1] = {true, true, true, true};
    const size_t len2 = 6;
    const bool number2[len2] = {false, false, true, true, true, true};
    return compare(number1, len1, number2, len2) == 0;
}

const bool testCase6(void)
{
    const size_t len1 = 4;
    const bool number1[len1] = {true, true, true, true};
    const size_t len2 = 6;
    const bool number2[len2] = {false, false, false, false, false, false};
    return compare(number1, len1, number2, len2) == 1;
}

const bool test(void)
{
    return testCase1() && testCase2 ()&& testCase3() && testCase4() && testCase5() && testCase6();
}
