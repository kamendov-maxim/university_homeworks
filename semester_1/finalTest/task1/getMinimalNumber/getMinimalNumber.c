
#include <string.h>
#include <stdlib.h>

#include "getMinimalNumber.h"

#include "../read/read.h"

static int compare(const void *a, const void *b)
{
    return *(const char *)a - *(const char *)b;
}

char * getMinimalNumber(char const * const  number)
{
    char *newNumber = copyString(number);
    if (newNumber == NULL)
    {
        return NULL;
    }

    qsort(newNumber, strlen(newNumber), sizeof(char), compare);

    return newNumber;
}