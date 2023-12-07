#include <stdio.h>

#include "workWithFile.h"
#include "../String/String.h"

FileWorkErrorCode scanWords(const char * const filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return accessErrorFile;
    }

    char * word = NULL;
    size_t len = 0;
    do
    {
        char * word = getString(&len, file, ' ');
        if (word == NULL)
        {
            fclose(file);
            // delete dictionary
            return memoryErrorFile;
        }
        
    

        if (word[0] != '\0')
        {
            // add word to dictionary
        }
        
    } while(word[0] != '\0');
    

    fclose(file);
    return okFile;
}
