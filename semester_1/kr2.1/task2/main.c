#include <stdio.h>

#include "workWithFile/workWithFile.h"
#include "graph/graph.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define ERROR_OCCURED 1

#define FILENAME "file.txt"

int main()
{
    Graph *graph = NULL;
    size_t nodeAmount = 0;
    WorkWithFileErrorCode errorCode = readTableFromFile(FILENAME, &graph, &nodeAmount);
    if (errorCode != okFile)
    {
        return ERROR_OCCURED;
    }
    
    printComponentsTable(graph, nodeAmount);
    return PROGRAM_FINISHED_CORRECTLY;
}
