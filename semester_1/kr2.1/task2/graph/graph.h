#pragma once
#include <stdlib.h>

typedef struct Graph Graph;

Graph *createGraph(const size_t nodeAmount, const size_t edgeAmount);
void connectNode(Graph *graph, size_t index, size_t nodeNumber);
void printComponentsTable(Graph *graph, const size_t nodeAmount);
void deleteGraph(Graph * const graph);

