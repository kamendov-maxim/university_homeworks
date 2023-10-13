#include "smartQuickSort.h"

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

bool testSwapFunction(void)
{
    int firstValue = 0;
    int secondValue = 1;
    swap(&firstValue, &secondValue);
    if (firstValue != 1 || secondValue != 0)
    {
        return false;
    }
    return true;
}

bool testStarterForArrays(int testArray[], int answerArray[], int size)
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

    int testArray2[6] = {43, 36, 55, 60, 94, 24};
    int answerArray2[6] = {24, 36, 43, 55, 60, 94};

    int testArray3[5] = {87, 91, 53, 37, 42};
    int answerArray3[5] = {37, 42, 53, 87, 91};

    int testArray4[1] = {5};
    int answerArray4[1] = {5};

    partition(testArray1, 0, 9);
    partition(testArray2, 0, 6);
    partition(testArray3, 0, 5);
    partition(testArray4, 0, 1);

    if (!(testStarterForArrays(testArray1, answerArray1, 9) * testStarterForArrays(testArray2, answerArray2, 6) * testStarterForArrays(testArray3, answerArray3, 5) * testStarterForArrays(testArray4, answerArray4, 1)))
    {
        return false;
    }

    return true;
}

bool testSmartQuickSortFunction(void)
{

    int testArray1[5] = {5, 4, 3, 2, 1};
    int answerArray1[5] = {1, 2, 3, 4, 5};

    int testArray2[5] = {1, 2, 3, 4, 5};
    int answerArray2[5] = {1, 2, 3, 4, 5};

    int testArray3[1] = {1};
    int answerArray3[1] = {1};

    int errorCode = smartQuickSort(testArray1, 0, 5 - 1);
    if (errorCode != 0)
    {
        return false;
    }

    errorCode = smartQuickSort(testArray2, 0, 5 - 1);
    if (errorCode != 0)
    {
        return false;
    }

    errorCode = smartQuickSort(testArray3, 0, 1 - 1);
    if (errorCode != 0)
    {
        return false;
    }

    if (!(testStarterForArrays(testArray1, answerArray1, 5) * testStarterForArrays(testArray2, answerArray2, 5) * testStarterForArrays(testArray3, answerArray3, 1)))
    {
        return false;
    }

    return true;
}

bool testSmartQuickSort(void)
{
    if (!(testSwapFunction() * testPartitionFunction() * testSmartQuickSortFunction()))
    {
        return false;
    }

    return true;
}

int smartQuickSort(int array[], int leftElement, int rightElement)
{
    if (rightElement < leftElement)
    {
        return 2;
    }

    if (rightElement - leftElement + 1 < 10)
    {
        int errorCode = insertSort(array, leftElement, rightElement + 1);
        if (errorCode != 0)
        {
            return 1;
        }
        return 0;
    }
    if (leftElement < rightElement)
    {
        int currentSeparator = partition(array, 0, rightElement);
        smartQuickSort(array, leftElement, currentSeparator - 1);
        smartQuickSort(array, currentSeparator + 1, rightElement);
    }
    return 0;
}