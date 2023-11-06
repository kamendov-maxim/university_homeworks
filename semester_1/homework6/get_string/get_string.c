#include <stdlib.h>
#include <stdio.h>

#include "get_string.h"

char *get_string(size_t * const len, FILE * filename)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));
    if (s == NULL)
    {
        return NULL;
    }

    for (char c = fgetc(filename); c != '\n' && c != EOF; c = fgetc(filename))
    {
        // printf("%c\n", c);
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
