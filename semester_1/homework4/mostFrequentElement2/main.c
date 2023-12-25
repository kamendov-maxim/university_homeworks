#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "smartQuickSort/smartQuickSort.h"
#include "smartQuickSort/tests/test.h"
#include "mostFrequentElement/mostFrequentElement.h"
#include "mostFrequentElement/tests/test.h"
#include "readFile/readFile.h"

#define FILENAME "../file.txt"

typedef enum ExitCode
{
    programFinishedCorrectly,
    programFailedTests,
    memoryError,
    fileReadingError,
    fileOpeningError
} ExitCode;

static void printArray(int const *const array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

const bool test(void)
{
    return testSmartQuickSort() && testMostFrequentElement();
}

ExitCode main()
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return programFailedTests;
    }

    size_t size = 0;
    fileReadingErrorCode errorCode = okFR;
    int *array = readArrayFromFile(FILENAME, &errorCode, &size);
    if (array == NULL)
    {
        char *message = '/0';
        switch (errorCode)
        {
        case openingFileErrorFR:
            printf("Cannot open the file\n");
            return fileOpeningError;

        case readingFileErrorFR:
            printf("Error occured while reading from file\n");
            return fileReadingError;

        case memoryErrorFR:
            printf("Not enough memory\n");
            return memoryError;

        default:
            return fileReadingError;
        }
    }

    printf("Array from file \"%s\": ", FILENAME);
    printArray(array, size);
    printf("\nThe most frequent element in the array is %d\n", mostFrequentElement(array, size));
    free(array);

    return programFinishedCorrectly;
}
