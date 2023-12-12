#include <stdbool.h>

#include "graph.h"
#include "../list/list.h"

typedef struct Edge
{
    size_t firstNodeNumber;
    size_t secondNodeNumber;
} Edge;

typedef struct Graph
{
    size_t edgeAmount;
    Edge **edges;
} Graph;

Graph *createGraph(const size_t nodeAmount, const size_t edgeAmount)
{
    Graph *graph = calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }

    Edge **edges = calloc(edges, sizeof(Edge *));
    if (edges == NULL)
    {
        free(graph);
        return NULL;
    }
    graph->edgeAmount = edgeAmount;
    graph->edges = edges;
}

void connectNode(Graph *graph, size_t index, size_t nodeNumber)
{
    Edge *edge = graph->edges[index];
    switch (edge->firstNodeNumber == 0)
    {
    case false:
    {
        edge->firstNodeNumber = nodeNumber;
        break;
    }

    case true:
    {
        edge->secondNodeNumber = nodeNumber;
        break;
    }

    default:
        break;
    }
}

static List **createComponentsTable(Graph *graph, const size_t nodeAmount)
{
    List **table = calloc(nodeAmount, sizeof(List *));
    if (table == NULL)
    {
        return NULL;
    }
    
    ListErrorCode listErrorCode = okList;
    for (size_t i = 0; i < graph->edgeAmount; i++)
    {
        Edge *currentEdge = graph->edges[i];
        for (size_t j = 0; j < nodeAmount; ++j)
        {
            if (!(checkValue(table[j], currentEdge->firstNodeNumber) || checkValue(table[j], currentEdge->secondNodeNumber)))
            {
                listErrorCode = append(table[i], currentEdge->firstNodeNumber);
                listErrorCode = append(table[i], currentEdge->secondNodeNumber);
                break;
            }
        }   
    }  
    return table;
}

void printComponentsTable(Graph *graph, const size_t nodeAmount)
{
    List ** componentsTable = createComponentsTable;
    if (componentsTable == NULL)
    {

        return;
    }
    
    for (size_t i = 0; i < nodeAmount; ++i)
    {
        printList(componentsTable[i]);
    }

    for (size_t i = 0; i < nodeAmount; ++i)
    {
        deleteList(componentsTable[i]);
    }
    free(componentsTable);
}

void deleteGraph(Graph * const graph)
{
    for (size_t i = 0; i < graph->edgeAmount; ++i)
    {
        free(graph->edges[i]);
    }
    free(graph);
}
