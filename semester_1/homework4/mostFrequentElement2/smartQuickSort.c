#include "smartQuickSort.h"
#include <stdlib.h>
#include <stdbool.h>

void swap(int *firstValue, int *secondValue)
{
    int buffer = *firstValue;
    *firstValue = *secondValue;
    *secondValue = buffer;
}

int partition(int array[], int leftElement, int rightElement)
{
    rightElement -= 1;
    int currentSeparator = array[leftElement];
    int i = rightElement;

    for (int j = rightElement; j > leftElement; --j)
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

int insertSort(int array[], int leftElement, int rightElement)
{
    if (rightElement < leftElement)
    {
        return 1;
    }

    for (int i = leftElement; i < rightElement; ++i)
    {
        int currentElement = array[i];
        int j = i - 1;
        while (j >= leftElement && array[j] >= currentElement)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = currentElement;
    }
    return 0;
}

static bool testSwapFunction(void)
{
    int firstValue = 0;
    int secondValue = 1;
    swap(&firstValue, &secondValue);
    return !(firstValue != 1 || secondValue != 0);
}

static bool compareArrays(int testArray[], int answerArray[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (testArray[i] != answerArray[i])
        {
            return false;
        }
    }
    return true;
}

bool testPartitionFunction(void)
{
    int testArray1[9] = {61, 99, 60, 80, 27, 57, 35, 81, 80};
    int answerArray1[9] = {27, 57, 60, 35, 61, 99, 80, 81, 80};
    const size_t size1 = 9;

    int testArray2[6] = {43, 36, 55, 60, 94, 24};
    int answerArray2[6] = {24, 36, 43, 55, 60, 94};
    const size_t size2 = 6;

    int testArray3[5] = {87, 91, 53, 37, 42};
    int answerArray3[5] = {37, 42, 53, 87, 91};
    const size_t size3 = 5;

    int testArray4[1] = {5};
    int answerArray4[1] = {5};
    const size_t size4 = 1;

    partition(testArray1, 0, size1);
    partition(testArray2, 0, size2);
    partition(testArray3, 0, size3);
    partition(testArray4, 0, size4);

    return compareArrays(testArray1, answerArray1, size1) && compareArrays(testArray2, answerArray2, size2) && compareArrays(testArray3, answerArray3, size3) && compareArrays(testArray4, answerArray4, size4);
}

static bool testSmartQuickSortFunction(void)
{

    int testArray1[5] = {5, 4, 3, 2, 1};
    int answerArray1[5] = {1, 2, 3, 4, 5};
    const size_t size1 = 5;

    int testArray2[5] = {1, 2, 3, 4, 5};
    int answerArray2[5] = {1, 2, 3, 4, 5};
    const size_t size2 = 5;

    int testArray3[1] = {1};
    int answerArray3[1] = {1};
    const size_t size3 = 1;

    smartQuickSort(testArray1, 0, size1 - 1);

    smartQuickSort(testArray2, 0, size2 - 1);

    smartQuickSort(testArray3, 0, size3 - 1);

    return compareArrays(testArray1, answerArray1, 5) && compareArrays(testArray2, answerArray2, 5) && compareArrays(testArray3, answerArray3, 1);
}

bool testSmartQuickSort(void)
{
    return testSwapFunction() && testPartitionFunction() && testSmartQuickSortFunction();
}

void smartQuickSort(int array[], int leftElement, int rightElement)
{

    if (rightElement - leftElement + 1 < 10)
    {
        int errorCode = insertSort(array, leftElement, rightElement + 1);
    }
    if (leftElement < rightElement)
    {
        int currentSeparator = partition(array, 0, rightElement);
        smartQuickSort(array, leftElement, currentSeparator - 1);
        smartQuickSort(array, currentSeparator + 1, rightElement);
    }
}
