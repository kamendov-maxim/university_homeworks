#pragma once

#include <stdlib.h>
#include "../graph/graph.h"

typedef enum WorkWithFileErrorCode
{
    okFile,
    accessErrorFile,
    memoryErrorFile,
    fileReadingErrorFile
} WorkWithFileErrorCode;

WorkWithFileErrorCode readTableFromFile(const char *const fileName, Graph **graph, size_t *nodeAmount);
