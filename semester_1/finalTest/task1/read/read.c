#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read.h"

const char * allowedCharacters = "0123456789";
const size_t allowedCharactersLen = 10;

char *getString(size_t * const len, FILE * file, char const endOfLine, bool *isNaturalNumber)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));
    if (s == NULL)
    {
        return NULL;
    }
    *isNaturalNumber = true;

    for (char c = fgetc(file); c != endOfLine && c != EOF; c = fgetc(file))
    {
        bool checkChar = false;
        for (size_t i = 0; i < allowedCharactersLen; ++i)
        {
            if (c == allowedCharacters[i])
            {
                checkChar = true;

                if (s[0] == '0' && *len + 1 > 1)
                {
                    checkChar = false;
                }
                break;
            }
        }
        if (!checkChar)
        {
            *isNaturalNumber = false;
            free(s);
            return "0";
        }
        
    

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
    }

    s[*len] = '\0';

    return s;
}

char *copyString(char const * const string)
{
    const size_t len = strlen(string);
    char *copy = (char *)malloc(len * sizeof(char));
    if (copy != NULL)
    {
        strcpy(copy, string);
    }
    return copy;
}
