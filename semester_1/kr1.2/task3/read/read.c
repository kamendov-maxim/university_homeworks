#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read.h"

char *getString(size_t *const len, char, char const endOfLine)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));
    if (s == NULL)
    {
        return NULL;
    }
    char previousChar = '\0';
    for (char c = fgetc(file); c != endOfLine && c != EOF; c = fgetc(file))
    {
        if (c != previousChar)   
        {
            s[(*len)++] = c;

            if (*len >= capacity)
            {
                capacity *= 2;
                char *tmp = (char *)realloc(s, capacity * sizeof(char));
                if (tmp == NULL)
                {
                    free(s);
                    return NULL;
                }
                s = tmp;
            }
            previousChar = c;
        }
    }

    s[*len] = '\0';

    return s;
}

char *copyString(char const *const string)
{
    const size_t len = strlen(string);
    char *copy = (char *)malloc(len * sizeof(char));
    if (copy != NULL)
    {
        strcpy(copy, string);
    }
    return copy;
}
