#include <string.h>
#include <ctype.h>

#include "checkString.h"

typedef enum State
{
    start,
    reading,
    finish,
    fail
} State;

static const State move(State const state, char const c)
{
    switch (state)
    {
    case start:
    {
        if (isalpha(c))
        {
            return reading;
        }
        return fail;
    }

    case reading:
    {
        if (isalpha(c) || isdigit(c) || c == '_')
        {
            return reading;
        }
        return fail;
    }

    default:
        return fail;
    }
}

const bool checkString(char const *const string)
{
    size_t len = strlen(string);
    State state = start;
    for (size_t i = 0; i < len; ++i)
    {
        char c = string[i];
        state = move(state, c);
        if (state == fail)
        {
            return false;
        }
    }
    
    return (state == start ? false: true);
}
