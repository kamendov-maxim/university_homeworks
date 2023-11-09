#include <stdlib.h>
#include <stdio.h>

#include "getString.h"

char *getString(size_t * const len, FILE * filename, char const endOfLine)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));
    if (s == NULL)
    {
        return NULL;
    }

    for (char c = fgetc(filename); c != endOfLine && c != '-' && c != EOF; c = fgetc(filename))
    {
        s[(*len)++] = c;

        if (*len >= capacity)
        {
            capacity *= 2;
            s = (char *)realloc(s, capacity * sizeof(char));
            if (s == NULL)
            {
                return NULL;
            }
        }
    }

    s[*len] = '\0';

    return s;
}
