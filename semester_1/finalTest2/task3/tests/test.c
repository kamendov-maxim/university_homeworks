#include <stdlib.h>
#include <stdio.h>
#include "test.h"
#include "../checkString/checkString.h"

const bool test(void)
{
    const size_t testNumber = 10;
    const char *const testStrings[testNumber] = {"ads34676_", "ва2345_3", "U", "F342", "QadfGfss_12343dfwgasf___", "2W", "Ф", "r", "", "432567854ew3"};
    const bool answers[testNumber] = {true, false, true, true, true, false, false, true, false, false};
    for (size_t i = 0; i < testNumber; ++i)
    {
        if (checkString(testStrings[i]) != answers[i])
        {
            return false;
        }
    }
    return true;
}
