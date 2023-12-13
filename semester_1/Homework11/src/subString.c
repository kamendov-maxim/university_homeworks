#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "../include/subString.h"

#define MEMORY_ERROR 2

static long *createLPSArray(char const *const pattern, const long pLength)
{
    long len = 0;
    long *lps = (long *)malloc(pLength * sizeof(long));
    if (lps == NULL)
    {
        return NULL;
    }

    lps[0] = 0;
    long i = 1;

    while (i < pLength)
    {
        if (pattern[i] == pattern[len])
        {
            ++len;
            lps[i] = len;
            ++i;
        }
        else if (len != 0)
        {
            len = lps[len - 1];
        }
        else
        {
            lps[i] = 0;
            ++i;
        }
    }

    return lps;
}

long findSubstring(char const *const pattern, char const *const text, ErrorCode *const errorCode)
{
    long pLength = strlen(pattern);
    long tLength = strlen(text);

    if (pLength == 0)
    {
        return 0;
    }

    if (pLength > tLength)
    {
        return -1;
    }

    long *lps = createLPSArray(pattern, pLength);
    if (lps == NULL)
    {
        *errorCode = memoryError;
    }
    *errorCode = ok;
    long j = 0;
    long i = 0;
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
