#include "isRealNumber.h"

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef enum State
{
    start,
    intPart,
    point,
    afterPointBeforeE,
    charE,
    signAfterE,
    digitsAfterE,
    finish,
    stop
} State;

static State move(State state, char c)
{
    State answer = state;
    switch (state)
    {
    case start:
    {
        if (isdigit(c))
        {
            return intPart;
        }
        return stop;
    }

    case intPart:
    {
        if (c == '.')
        {
            return point;
        }
        else if (isdigit(c))
        {
            return intPart;
        }
        else if (c == 'E')
        {
            return charE;
        }
        if (c == '\0')
        {
            return finish;
        } 
        return stop;
    }

    case point:
    {
        if (isdigit(c))
        {
            return afterPointBeforeE;
        }
        return stop;
    }

    case afterPointBeforeE:
    {
        if (isdigit(c))
        {
            return afterPointBeforeE;
        }
        else if (c == 'E')
        {
            return charE;
        }
        if (c == '\0')
        {
            return finish;
        } 
        return stop;
    }

    case charE:
    {
        if (c == '+' || c == '-')
        {
            return signAfterE;
        }
        if (isdigit(c))
        {
            return digitsAfterE;
        }
        return stop;
    }

    case signAfterE:
    {
        if (isdigit(c))
        {
            return digitsAfterE;
        }
        return stop;
    }

    case digitsAfterE:
    {
        if (isdigit(c))
        {
            return digitsAfterE;
        }
        if (c == '\0')
        {
            return finish;
        }   
    }

    default:
        return stop;
    }
}

const bool isRealNumber(char const * const input)
{
    State state = start;
    size_t len = strlen(input);
    for (size_t i = 0; i < len; ++i)
    {
        char currentCharacter = input[i];
        state = move(state, currentCharacter);
        if (state == stop)
        {
            return false;
        }
    }
    if (state ==  intPart || state == digitsAfterE || state == afterPointBeforeE)
    {
        state = finish;
    }
    
    return (state == finish  ? true : false);
}


