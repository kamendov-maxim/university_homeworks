#include <stdio.h>

#include "readFile.h"

int *readArrayFromFile(char const *const fileName, fileReadingErrorCode * const errorCode, size_t *size)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        *errorCode = openingFileErrorFR;
        return NULL;
    }

    if (fscanf(file, "%zd", size) != 1)
    {
        fclose(file);
        *errorCode = readingFileErrorFR;
        return NULL;
    }

    int *array = (int *)malloc(*size * sizeof(int));
    if (array == NULL)
    {
        fclose(file);
        *errorCode = memoryErrorFR;

        return NULL;
    }

    for (size_t i = 0; i < *size; ++i)
    {
        int number = 0;
        if (fscanf(file, "%d", &number) != 1)
        {
            *errorCode = readingFileErrorFR;
            fclose(file);
            free(array);
            return NULL;
        }
        array[i] = number;
    }

    *errorCode = okFR;
    return array;
}
