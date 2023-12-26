#pragma once

#include <stdlib.h>

typedef enum fileReadingErrorCode
{
    okFR,
    memoryErrorFR,
    openingFileErrorFR,
    readingFileErrorFR
} fileReadingErrorCode;

int *readArrayFromFile(char const *const fileName, fileReadingErrorCode * const errorCode, size_t *size);
