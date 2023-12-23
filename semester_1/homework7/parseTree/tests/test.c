#include <stdio.h>
#include <stdlib.h>

#include "../parseTree/parseTree.h"
#include "test.h"
#include "../String/String.h"

const bool testCase(char const * const testFile)
{
    FILE * file = fopen(testFile, "r");
    if (file == NULL)
    {
        printf("12313");
        return false;
    }
    char *expression = getString(file, '\n');
    float testAnswer = 0;
    fscanf(file, "%f", &testAnswer);
    fclose(file);
    if (expression == NULL)
    {
        printf("e");
        return false;
    }
    ParseTree *tree = createTree(expression);
    free(expression);
    float answer = calculate(tree);
    deleteTree(&tree); 
    return answer == testAnswer;    
}

const bool test(void)
{
    const size_t testNumber = 3;
    char const * const testFiles[testNumber] = {"../tests/testFile1.txt", "../tests/testFile2.txt", "../tests/testFile3.txt"};
    for (size_t i = 0; i < testNumber; ++i)
    {
        if (!testCase(testFiles[i]))
        {
            printf("%lu\n", i);
            return false;
        }
    }
    
    return true;
}
