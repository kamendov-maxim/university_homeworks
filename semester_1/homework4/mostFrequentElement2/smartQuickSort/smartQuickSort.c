#include <stdbool.h>

#include "smartQuickSort.h"

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

void smartQuickSort(int *const array, size_t leftElement, size_t rightElement)
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
