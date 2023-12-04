#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "smartQuickSort/smartQuickSort.h"
#include "smartQuickSort/tests/test.h"

#define filename "file.txt"
#define PROGRAM_FINISHED_CORRECTLY 0
#define TESTS_ARE_NOT_PASSES 1
#define MEMORY_ERROR 2
#define FILE_READING_ERROR 3

static void printArray(int const *const array, size_t const size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf('\n');
}

static int mostFrequentElement(int *array, size_t size)
{
    int mostFrequentElement = array[0];
    int counter = 1;
    int maxCount = 1;
    for (int i = 1; i < size; ++i)
    {
        if (array[i] == array[i - 1])
        {
            ++counter;
            if (counter > maxCount)
            {
                maxCount = counter;
                mostFrequentElement = array[i];
            }
        }
        else
        {
            counter = 1;
        }
    }
    return mostFrequentElement;
}

static const bool testCaseForMostFrequentELement(int testArray[], int size, int answer)
{
    return mostFrequentElement(testArray, size) != answer;
}

static const bool testMostFrequentElementFunction(void)
{
    int testArray1[10] = {1, 3, 4, 4, 5, 6, 7, 7, 7, 8};
    int answer1 = 7;

    int testArray2[4] = {3, 0, 0, 5};
    int answer2 = 0;

    int testArray3[1] = {0};
    int answer3 = 0;

    return testCaseForMostFrequentELement(testArray1, 10, answer1) && testCaseForMostFrequentELement(testArray2, 4, answer2) && testCaseForMostFrequentELement(testArray3, 1, answer3);
}

static bool const test(void)
{
    return testMostFrequentElementFunction() && testSmartQuickSort();
}

static int *fileReading(char const *const fileName, size_t *const size)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        exit(MEMORY_ERROR);
    }

    if (fscanf(file, "%zd", size) != 1)
    {
        fclose(file);
        exit(FILE_READING_ERROR);
    }

    int *array = (int *)malloc((*size) * sizeof(int));
    if (array == NULL)
    {
        fclose(file);
        exit(MEMORY_ERROR);
    }

    for (size_t i = 0; i < *size; ++i)
    {
        if (fscanf(file, "%d", &array[i]) != 1)
        {
            fclose(file);
            free(array);
            exit(FILE_READING_ERROR);
        }
    }

    fclose(file);
    return array;
}

int main(void)
{
    // if (!test())
    // {
    //     printf("\nSorry but the program does not work correctly\n");
    //     return testsAreNotPassedError;
    // }

    size_t size = 0;
    int *array = fileReading(filename, &size);

    printf("Numbers from the file:\n");
    printArray(array, size);
    printf("dasads");

    smartQuickSort(array, 0, size - 1);
    printf("sdad");

    printf("\nThe most frequent element in the file is %d\n", mostFrequentElement(array, size + 1));
    printArray(array, size);
    free(array);

    return PROGRAM_FINISHED_CORRECTLY;
}
