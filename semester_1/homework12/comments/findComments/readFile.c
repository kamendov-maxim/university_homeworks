#include <stdio.h>

#include "readFile.h"
#include "errorCode.h"
#include "../../String/String.h"

char * readFile(const char * const fileName, size_t *len)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }
    char * text = getString(len, file, EOF);
    fclose(file);
    return text;
}
