#include <stdbool.h>

#include "test.h"
#include "../list/list.h"

static bool testCase(const size_t n, const size_t m, const size_t answer)
{
    ListErrorCode listErrorCode = ok;
    return (count(n, m, &listErrorCode) == answer && listErrorCode == ok);
}

bool test(void)
{
    bool testCase1 = testCase(10, 3, 4);
    bool testCase2 = testCase(6, 2, 5);
    bool testCase3 = testCase(6, 5, 1);

    return testCase1 && testCase2 && testCase3;
}
