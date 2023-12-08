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
    Edge **edges;
} Graph;

Graph *createGraph(const size_t nodes, const size_t edges)
{
    Graph *graph = calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }

    Edge **edges = calloc(edges, sizeof(*Edge));
    if (edges == NULL)
    {
        free(graph);
        return NULL;
    }
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

List *createComponentsTable(Graph *graph, const size_t nodes)
{
    List **table = calloc(nodes, sizeof(*List));
    if (table == NULL)
    {
        return NULL;
    }
    
}