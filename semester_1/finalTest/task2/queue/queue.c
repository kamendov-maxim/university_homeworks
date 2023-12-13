
#include <stdlib.h>

#include "queue.h"

typedef struct Node
{
    size_t priority;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *head;
} Queue;

Queue *createQueue(void){
    return (Queue *)calloc(1, sizeof(Queue));
}

ErrorCode enqueue(Queue * const queue,const int value, const size_t priority)
{
    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return memoryError;
    }
    newNode->priority = priority;
    newNode->value = value;
    Node **currentNode = &(queue->head);
    for (; (*currentNode) != NULL; currentNode = &((*currentNode)->next))
    {
        if ((*currentNode)->priority < priority)
        {
            newNode->next = (*currentNode);
            *currentNode = newNode;
            return ok;
        }
    }
    *currentNode = newNode;
    return ok;
}

int dequeue(Queue * const queue, const int value)
{
    if (queue->head == NULL)
    {
        return -1;
    }
    Node *node = queue->head;
    int value = node->value;
    queue->head = node->next;
    free(node);
    return value;
}

void deleteQueue(Queue * const queue)
{
    for (Node * currentNode = queue->head; currentNode != NULL; currentNode = currentNode->next)
    {
        free(currentNode);
    }
    free(queue);
    queue = NULL;
}