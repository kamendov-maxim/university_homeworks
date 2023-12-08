#include <stdio.h>

#include "workWithFile.h"
#include "../String/String.h"
#include "../graph/graph.h"

static WorkWithFileErrorCode getTableSize(size_t *n, size_t *m, FILE *file)
{
    if (fscanf(file, "%s %s", n, m) != 2)
    {
        return fileReadingErrorFile;
    }

    return okFile;
}

WorkWithFileErrorCode readTableFromFile(const char *const fileName, Graph **graph, size_t *nodeAmount)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        return accessErrorFile;
    }
    size_t n = 0;
    size_t m = 0;
    if (getTableSize(&n, &m, file) != okFile)
    {
        fclose(file);
        return fileReadingErrorFile;
    }

    Graph *newGraph = createGraph(n, m);
    if (newGraph == NULL)
    {
        fclose(file);
        return memoryErrorFile;
    }
    

    size_t len = 0;
    for (size_t i = 0; i < n; ++i)
    {
        char *currentLine = getString(&len, file, '\n');
        if (currentLine == NULL)
        {
            fclose(file);
            deleteGraph(newGraph);
            return memoryErrorFile;
        }
        char currentChar = '\0';
        size_t counter = 0;
        do
        {
            currentChar = getc(currentLine);
            if (currentChar == '1' || currentChar == '0')
            {
                ++counter;
                if (currentChar == '1')
                {
                    connectNode(newGraph, counter, i);
                }
            }

        } while (currentChar != '\0');
    }
    fclose(file);

    *graph = newGraph;
    deleteGraph(newGraph);
    return okFile;
}