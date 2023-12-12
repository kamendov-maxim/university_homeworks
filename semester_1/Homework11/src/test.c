#include <stdio.h>
#include <stdlib.h>

#include "../include/test.h"
#include "../include/String.h"
#include "../include/subString.h"

static const bool testCase(const char *const testFileName, const char *const answerFileName)
{
    FILE *testFile = fopen(testFileName, "r");
    if (testFile == NULL)
    {
        return false;
    }

    size_t len = 0;
    char *pattern = getString(&len, testFile, '\n');
    if (pattern == NULL)
    {
        fclose(testFile);
        return false;
    }

    char *text = getString(&len, testFile, EOF);
    fclose(testFile);
    if (text == NULL)
    {
        free(pattern);
        return false;
    }
    ErrorCode errorCode = ok;
    long position = findSubstring(pattern, text, &errorCode);
    free(pattern);
    free(text);
    if (errorCode != ok)
    {
        return false;
    }

    FILE *answerFile = fopen(answerFileName, "r");
    if (answerFile == NULL)
    {
        return false;
    }
    
    long answer = 0;
    int scanfCheck = fscanf(answerFile, "%ld", &answer);
    fclose(answerFile);
    return scanfCheck == 1 && position == answer;
}

const bool test(void)
{
    const size_t testNumber = 3;
    const char *const testFileNames[testNumber] = {"../testFiles/test1.txt",
                                                   "../testFiles/test2.txt",
                                                   "../testFiles/test3.txt"};
    const char *const answerFileNames[testNumber] = {"../testFiles/answer1.txt",
                                                     "../testFiles/answer2.txt",
                                                     "../testFiles/answer3.txt"};
    for (size_t i = 0; i < testNumber; ++i)
    {
        if (!testCase(testFileNames[i], answerFileNames[i]))
        {
            return false;
        }
    }

    return true;
}
