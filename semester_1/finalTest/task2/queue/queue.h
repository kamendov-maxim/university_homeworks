#pragma once

typedef enum ErrorCode
{
    ok,
    memoryError
} ErrorCode;

typedef struct Queue Queue;

ErrorCode enqueue(Queue * const queue,const int value, const size_t priority);
void deleteQueue(Queue * const queue);
int dequeue(Queue * const queue, const int value);
