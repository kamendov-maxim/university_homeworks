#include "compareBinaryNumbers.h"

const int compare(const bool *const number1, const size_t len1,
                   const bool *const number2, const size_t len2)
{
    size_t minLength = 0;
    size_t maxLength = 0;
    bool *biggerArray = NULL;
    bool *smallerArray = NULL;
    int multiplier = 0;
    if (len1 > len2)
    {
        minLength = len2;
        maxLength = len1;
        biggerArray = number1;
        smallerArray = number2;
        multiplier = 1;
    }
    else
    {
        minLength = len1;
        maxLength = len2;
        biggerArray = number2;
        smallerArray = number1;
        multiplier = -1;
    }

size_t i = 0;
    for (; i < maxLength - minLength; i++)
    {
        if (biggerArray[i])
        {
            return multiplier;
        }
    }

    for (size_t j = 0; j < minLength; ++j)
    {
        if (smallerArray[j] != biggerArray[j+i])
        {
            return (biggerArray[j+i] ? 1 : -1) * multiplier;
        }
    }
    
    return 0;
}