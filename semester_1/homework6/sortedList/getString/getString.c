#include <stdlib.h>
#include <stdio.h>

#include "getString.h"

char *getString(size_t *const len)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));
    
    if (s == NULL)
    {
        return NULL;
    }

    for (char c = fgetc(stdin); c != '\n' && c != EOF && c != '-' && c != '\0'; c = fgetc(stdin))
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