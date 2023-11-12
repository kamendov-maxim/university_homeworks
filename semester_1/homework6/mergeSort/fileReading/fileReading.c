#include "fileReading.h"
#include "../listMergeSort/list.h"
#include "../../String/String.h"

#define OK 0
#define DATA_BASE_FILE_WAS_NOT_FOUND 1
#define MEMORY_ERROR 2
#define PROBLEM_WITH_LIST 3

int fileReading(List *const list, char const *const filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return DATA_BASE_FILE_WAS_NOT_FOUND;
    }
    size_t len = 0;
    while (!feof(file))
    {
        char *str = getString(&len, file, '\n');
        if (str == NULL)
        {
            deleteList(list);
            return MEMORY_ERROR;
        }

        char *name = (char *)malloc(sizeof(char));
        if (name == NULL)
        {
            return MEMORY_ERROR;
        }
        char *number = (char *)malloc(sizeof(char));
        if (number == NULL)
        {
            return MEMORY_ERROR;
        }

        bool flag = false;
        char *ptr = name;
        size_t startLength = 0;
        size_t nameLen = 0;
        for (size_t i = 0; str[i] != '\0'; ++i)
        {
            if (str[i] == '-')
            {
                ptr = number;
                startLength = nameLen + 1;
                continue;
            }
            ptr[i - startLength] = str[i] ;
            ++nameLen;
        }

        ListErrorCode listErrorCode = append(list, name, number, false);
        if (listErrorCode != ok)
        {
            free(name);
            free(number);
            deleteList(list);
            return PROBLEM_WITH_LIST;
        }
    }
    fclose(file);
    return OK;
}
