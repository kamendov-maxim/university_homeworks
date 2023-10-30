#include <stdlib.h>
#include <stdio.h>

#include "get_string.h"

char *get_string(size_t * const len)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));

    for (char c = getchar(); c != '\n'; c = getchar())
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
