#include <stdio.h>
#include <string.h>

#include "test.h"
#include "../findComments/findComments.h"

static const bool testCase(char const *const fileName, char const *const *const answers, size_t const answersSize)
{
    size_t len = 0;
    char **comments = findComments(fileName, &len);

    if (len != answersSize)
    {
        return false;
    }

    for (size_t i = 0; i < answersSize; ++i)
    {
        if (strcmp(comments[i], answers[i]) != 0)
        {
            free(comments);
            return false;
        }
    }
    free(comments);
    return true;
}

const bool test(void)
{
    char const * const testFile = "../tests/testFile.txt";
    size_t const answersSize = 3;
    char  const *const answers[answersSize] = { "/* fdga f/ afga */", "/*d*/", "/*  */"} ;

    return testCase(testFile, answers, answersSize);
}
