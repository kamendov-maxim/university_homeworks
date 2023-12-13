#include <stdlib.h>

#include "test.h"
#include "../queue/queue.h"

typedef enum Command
{
    enq,
    deq
} Command;

const bool testCase(Command const *const commands, size_t const *const priorities, int const *const answers, const size_t testLen)
{
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
            
            break;
        }

        case deq:
        {
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
