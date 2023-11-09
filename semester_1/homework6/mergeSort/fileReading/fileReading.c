#include "fileReading.h"
#include "../listMergeSort/list.h"
#include "../../getString/getString.h"

#define OK 0
#define DATA_BASE_FILE_WAS_NOT_FOUND 1
#define MEMORY_ERROR 2
#define PROBLEM_WITH_LIST 3


int fileReading(List * const list, char const *const filename, const bool copyRequired)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return DATA_BASE_FILE_WAS_NOT_FOUND;
    }
    size_t len = 0;
    while (!feof(file))
    {
        char *name = getString(&len, file, '\n');
        if (name == NULL)
        {
            deleteList(list);
            return MEMORY_ERROR;
        }

        char *number = getString(&len, file, '\n');
        if (number == NULL)
        {
            free(name);
            deleteList(list);
            return MEMORY_ERROR;
        }

        ListErrorCode listErrorCode = append(list, name, number, copyRequired);
        if (listErrorCode != ok)
        {
            free(name);
            free(number);
            deleteList(list);
            return PROBLEM_WITH_LIST;
        }
        printf("%s\n", name);
        printf("%s\n", number);

    }
    fclose(file);
    return OK;
}
