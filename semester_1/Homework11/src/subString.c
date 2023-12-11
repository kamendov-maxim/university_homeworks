#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "../include/subString.h"

#define MEMORY_ERROR 2

static size_t *createLPSArray(char const *const pattern, const size_t pLength)
{
    size_t len = 0;
    size_t *lps = (size_t *)malloc(pLength * sizeof(size_t));

    lps[0] = 0;
    size_t i = 1;

    while (i < pLength)
    {
        if (pattern[i] == pattern[len])
        {
            ++len;
            lps[i] = len;
            ++i;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                ++i;
            }
        }
    }

    return lps;
}

size_t findSubstring(char const *const pattern, char const *const text, ErrorCode *const errorCode)
{
    size_t pLength = strlen(pattern);
    size_t tLength = strlen(text);

    if (pLength == 0)
    {
        return 0;
    }

    if (pLength > tLength)
    {
        return -1;
    }

    size_t *lps = createLPSArray(pattern, pLength);
    if (lps == NULL)
    {
        *errorCode = memoryError;
    }
    *errorCode = ok;
    size_t j = 0;
    size_t i = 0;
    while (i < tLength)
    {
        if (pattern[j] == text[i])
        {
            ++j;
            ++i;
        }

        if (j == pLength)
        {
            free(lps);
            return i - j + 1;
        }

        else if (i < tLength && pattern[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    free(lps);
    return -1;
}
