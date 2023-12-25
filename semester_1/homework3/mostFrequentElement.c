#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum ExitCode
{
    programFinishedCorrectly,
    programFailedTests,
    memoryError,
    inputError
} ExitCode;

static int mostFrequentElement(int const *const array, const size_t size)
{
    int mostFrequentElement = array[0];
    size_t counter = 1;
    size_t maxCount = 1;
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

static void printArray(int const *const array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

static void swap(int *const firstValue, int *const secondValue)
{
    int buffer = *firstValue;
    *firstValue = *secondValue;
    *secondValue = buffer;
}

static size_t partition(int *const array, size_t leftElement, size_t rightElement)
{
    rightElement -= 1;
    int currentSeparator = array[leftElement];
    size_t i = rightElement;

    for (size_t j = rightElement; j > leftElement; --j)
    {
        if (array[j] >= currentSeparator)
        {
            swap(&array[i], &array[j]);
            --i;
        }
    }

    swap(&array[i], &array[leftElement]);

    return i;
}

static void insertSort(int *const array, size_t rightElement)
{
    size_t leftElement = 0;
    for (size_t i = leftElement + 1; i < rightElement; ++i)
    {
        int currentElement = array[i];
        int j = i - 1;
        bool f = false;
        while (j >= leftElement && array[j] >= currentElement)
        {
            array[j + 1] = array[j];
            f = true;
            if (j == 0)
            {
                break;
            }
            --j;
        }
        if (f)
        {
            array[j] = currentElement;
        }
    }
}

static void smartQuickSort(int *const array, size_t leftElement, size_t rightElement)
{
    if (rightElement - leftElement + 1 < 10)
    {
        insertSort(array, rightElement + 1);
        return;
    }
    if (leftElement < rightElement)
    {
        int currentSeparator = partition(array, 0, rightElement);
        smartQuickSort(array, leftElement, currentSeparator - 1);
        smartQuickSort(array, currentSeparator + 1, rightElement);
    }
}

static const bool testSwapFunction(void)
{
    int firstValue = 0;
    int secondValue = 1;
    swap(&firstValue, &secondValue);
    return firstValue == 1 && secondValue == 0;
}

static const bool testPartitionFunction(void)
{
    const size_t testSize1 = 9;
    int testArray1[testSize1] = {61, 99, 60, 80, 27, 57, 35, 81, 80};
    int const answerArray1[testSize1] = {27, 57, 60, 35, 61, 99, 80, 81, 80};

    const size_t testSize2 = 6;
    int testArray2[testSize2] = {43, 36, 55, 60, 94, 24};
    int const answerArray2[testSize2] = {24, 36, 43, 55, 60, 94};

    const size_t testSize3 = 5;
    int testArray3[testSize3] = {87, 91, 53, 37, 42};
    int const answerArray3[testSize3] = {37, 42, 53, 87, 91};

    const size_t testSize4 = 1;
    int testArray4[testSize4] = {5};
    int const answerArray4[testSize4] = {5};

    partition(testArray1, 0, testSize1);
    partition(testArray2, 0, testSize2);
    partition(testArray3, 0, testSize3);
    partition(testArray4, 0, testSize4);

    return memcmp(testArray1, answerArray1, testSize1) == 0
    && memcmp(testArray2, answerArray2, testSize2) == 0
    && memcmp(testArray3, answerArray3, testSize3) == 0
    && memcmp(testArray4, answerArray4, testSize4) == 0;
}

static const bool testSmartQuickSort(void)
{
    const size_t testSize1 = 5;
    int testArray1[testSize1] = {5, 4, 3, 2, 1};
    int answerArray1[testSize1] = {1, 2, 3, 4, 5};

    const size_t testSize2 = 5;
    int testArray2[testSize2] = {1, 2, 3, 4, 5};
    int answerArray2[testSize2] = {1, 2, 3, 4, 5};

    const size_t testSize3 = 1;
    int testArray3[testSize3] = {1};
    int answerArray3[testSize3] = {1};

    smartQuickSort(testArray1, 0, testSize1 - 1);
    smartQuickSort(testArray2, 0, testSize2 - 1);
    smartQuickSort(testArray3, 0, testSize3 - 1);

    return memcmp(testArray1, answerArray1, testSize1) == 0
    && memcmp(testArray2, answerArray2, testSize2) == 0
    && memcmp(testArray3, answerArray3, testSize3) == 0;
}

static const bool testMostFrequentElement(void)
{
    const size_t testSize1 = 10;
    const int testArray1[testSize1] = {1, 3, 4, 4, 5, 6, 7, 7, 7, 8};
    const int answer1 = 7;

    const size_t testSize2 = 4;
    const int testArray2[testSize2] = {3, 0, 0, 5};
    const int answer2 = 0;

    const size_t testSize3 = 1;
    const int testArray3[testSize3] = {0};
    const int answer3 = 0;

    return mostFrequentElement(testArray1, testSize1) == answer1
    && mostFrequentElement(testArray2, testSize2) == answer2
    && mostFrequentElement(testArray3, testSize3) == answer3;
}

const bool test(void)
{
    return testSwapFunction()
    && testPartitionFunction()
    && testSmartQuickSort()
    && testMostFrequentElement();
}

ExitCode main()
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return programFailedTests;
    }

    size_t size = 0;
    while (size == 0)
    {
        printf("Enter the size of your array: ");
        if (scanf("%zd", &size) != 1)
        {
            printf("Input error\n");
            return inputError;
        }
        if (size == 0)
        {
            printf("\nSize of your array should be at least 1\n");
        }
    }

    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL)
    {
        printf("\nNot enough memory\n");
        return memoryError;
    }

    printf("Enter numbers of your array one by one each other on the next line: \n");
    for (size_t i = 0; i < size; ++i)
    {
        printf("Enter %zd number of your array: ", i + 1);
        int currentNumber = 0;
        if (scanf("%d", &currentNumber) != 1)
        {
            printf("Input error\n");
            return inputError;
        }
        array[i] = currentNumber;
    }

    smartQuickSort(array, 0, size - 1);

    printf("\nThe most frequent element in the array is %d\n", mostFrequentElement(array, size));
    free(array);

    return programFinishedCorrectly;
}
