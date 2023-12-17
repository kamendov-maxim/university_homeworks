#include <stdlib.h>

#include "test.h"
#include "../isRealNumber/isRealNumber.h"

const bool test(void)
{
    const size_t testNumber = 10;
    const char *const strings[testNumber] = {"5", "6.7", "34.65E54", "E23", ".34",
                                             "dsffa", "", "0.4E-5", "98E+65", "12E2"};
    const bool answers[testNumber] = {true, true, true, false, false, false, false, true, true, true};

    for (size_t i = 0; i < testNumber; ++i)
    {
        if (isRealNumber(strings[i]) != answers[i])
        {
            return false;
        }
    }
    return true;
}
