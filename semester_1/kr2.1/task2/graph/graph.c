#include <stdlib.h>
#include <stdbool.h>

#include "../list/list.h"

typedef struct Edge
{
    size_t firstNodeNumber;
    size_t secondNodeNumber;
} Edge;

typedef struct Node
{
    /* data */
} Node;

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

List **createComponentsTable(Graph *graph, const size_t nodeAmount)
{
    List **table = calloc(nodeAmount, sizeof(List *));
    if (table == NULL)
    {
        return NULL;
    }
    
    ListErrorCode listErrorCode = okList;
    for (size_t i = 0; i < nodeAmount; i++)
    {
        Edge *currentEdge = graph->edges[i];
        for (size_t j = 0; j < nodeAmount; ++j)
        {
            if (!(checkValue(table[i], currentEdge->firstNodeNumber) || checkValue(table[i], currentEdge->secondNodeNumber)))
            {
                listErrorCode = append(table[i], currentEdge->firstNodeNumber);
                listErrorCode = append(table[i], currentEdge->secondNodeNumber);
            }
            
        }
        
    }
    
}