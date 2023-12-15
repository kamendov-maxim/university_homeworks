#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "../read/read.h"

const bool testCase(char const *const testFileName, char const *const answerFileName)
{
    FILE *file = fopen(testFileName, "r");
    if (file == NULL)
    {
        return false;
    }
    size_t len = 0;
    char * str = getString(&len, file, EOF);
    fclose(file);
    if (str == NULL)
    {
        return false;
    }
    FILE *answerFile = fopen(answerFileName, "r");
    if (answerFile == NULL)
    {
        free(str);
        return false;
    }
    char * str2 = getString(&len, answerFile, EOF);
    fclose(answerFile);
    if (str2 == NULL)
    {
        free(str1);
        return false;
    }
    
    
}

const bool test(void)
{
    const size_t testNumber = 3;
    char const *const testFileNames[testNumber] = {"../tests/testFile1.txt", "../tests/testFile2.txt", "../tests/testFile3.txt"};
    char const *const answerFileNames[testNumber] = {"../tests/answerFile1.txt",
                                                     "../tests/answerFile1.txt",
                                                     "../tests/answerFile1.txt"};

    for (size_t i = 0; i < testNumber; ++i)
    {
        FILE *file = fopen(FILENAME, "r");
        if (file == NULL)
        {
            return false;
        }
        fclose(file);
    }
}
