#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "String.h"

char *getString(size_t * const len, FILE * filename, char const endOfLine)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));
    if (s == NULL)
    {
        return NULL;
    }

    for (char c = fgetc(filename); c != endOfLine && c != EOF; c = fgetc(filename))
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

char *copyString(char * const string)
{
    const size_t len = strlen(string);
    char *copy = (char *)malloc(len * sizeof(char));
    if (copy != NULL)
    {
        strcpy(copy, string);
    }
    return copy;
}
