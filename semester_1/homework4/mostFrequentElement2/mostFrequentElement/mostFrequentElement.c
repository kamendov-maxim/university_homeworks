#include "mostFrequentElement.h"

int mostFrequentElement(int const *const array, const size_t size)
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
