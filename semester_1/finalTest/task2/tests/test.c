#include <stdlib.h>

#include "test.h"
#include "../queue/queue.h"

typedef enum Command
{
    enq,
    deq
} Command;

const bool testCase(Command const *const commands, size_t const *const priorities,
int const *const answers, const size_t testLen, const int * const values)
{
    size_t currentPriority = 0;
    size_t currentAnswer = 0;
    size_t currentValue = 0;
    Queue *queue = createQueue();
    if (queue == NULL)
    {
        return false;
    }
    
    for (size_t i = 0; i < testLen; ++i)
    {
        switch (commands[i])
        {
        case enq:
        { 
            ErrorCode ec = enqueue(queue, values[currentValue], priorities[currentPriority]);
            if (ec != ok)
            {
                deleteQueue(queue);
                return false;
            }
            ++currentValue;
            ++currentPriority;
            break;
        }

        case deq:
        {
            int value = dequeue(queue);
            if (value != values[currentValue])
            {
                deleteQueue(queue);
                return false;
            }
            ++currentValue;
            break;
        }

        default:
            break;
        }
    }
}

const bool test(void)
{
    return true;
}
