#include <stdio.h>
#include <stdlib.h>

#include "../include/String.h"

#define MEMORY_ERROR 2
#define FILE_ERROR 3

char *readFile(const char *const fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        exit(FILE_ERROR);
    }
    size_t len = 0;
    char *str = getString(&len, file, EOF);
    fclose(file);
    if (str == NULL)
    {
        exit(MEMORY_ERROR);
    }
    
    return str;
}