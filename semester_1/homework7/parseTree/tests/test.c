#include <stdio.h>
#include <stdlib.h>

#include "../parseTree/parseTree.h"
#include "test.h"
#include "../String/String.h"

const bool testCase(char const *const testFile)
{
    FILE *file = fopen(testFile, "r");
    if (file == NULL)
    {
        return false;
    }
    char *expression = getString(file, '\n');
    float testAnswer = 0;
    fscanf(file, "%f", &testAnswer);
    fclose(file);
    if (expression == NULL)
    {
        return false;
    }
    ParseTree *tree = createTree(expression);
    free(expression);
    if (tree == NULL)
    {
        return false;
    }

    bool wrongOperation = false;
    float answer = calculate(tree, &wrongOperation);
    deleteTree(&tree);
    if (wrongOperation)
    {
        return false;
    }

    return answer == testAnswer;
}

const bool test(void)
{
    const size_t testNumber = 4;
    char const *const testFiles[testNumber] = {"../tests/testFile1.txt", "../tests/testFile2.txt", "../tests/testFile3.txt", "../tests/testFile4.txt"};
    for (size_t i = 0; i < testNumber; ++i)
    {
        if (!testCase(testFiles[i]))
        {
            return false;
        }
    }

    return true;
}
