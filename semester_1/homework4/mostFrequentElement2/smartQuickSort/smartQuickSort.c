#include "smartQuickSort.h"
#include <stdlib.h>
#include <stdbool.h>

static void swap(int *firstValue, int *secondValue)
{
    int buffer = *firstValue;
    *firstValue = *secondValue;
    *secondValue = buffer;
}

static int partition(int array[], int leftElement, int rightElement)
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

int insertSort(int * const array, const int leftElement, const int rightElement)
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

void smartQuickSort(int * const array, const int leftElement, const int rightElement)
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
