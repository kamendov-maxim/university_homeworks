#include <stdio.h>
#include <stdlib.h>

#include "read/read.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define FILE_READING_ERROR 3

#define FILENAME "../file.txt"

int main(void)
{
    // if (!test())
    // {
    //     printf("Программа сейчас не работает\n");
    //     return PROGRAM_FAILED_TESTS;
    // }
    
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Не удается получить доступ к файлу\n");
        return FILE_READING_ERROR;
    }
    

    size_t len = 0;
    char *text = getString(&len, file, EOF);
    fclose(file);
    if (text == NULL)
    {
        printf("Закончилась память\n");
        return MEMORY_ERROR;
    }
    printf("%s\n", text);
    free(text);
}
