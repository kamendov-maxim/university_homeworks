#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "read/read.h"
#include "getMinimalNumber/getMinimalNumber.h"
#include "tests/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2

int compare(const void *a, const void *b)
{
    return *(const char *)a - *(const char *)b;
}
// int comp (const char element1, const char element2)
// {
//     if (element1 == element2)
//     {
//         return 0;
//     }

//     return (element1 < element2 ? -1 : 1);
// }

static clear(void)
{
    while (getchar() != '\n')
        ;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    if (!test())
    {
        printf("Программа не работает\n");
        return PROGRAM_FAILED_TESTS;
    }
    
    size_t len = 2;
    char *number = "00";
    bool isNaturalNUmber = false;
    while (!isNaturalNUmber)
    {
        printf("Ведите число: ");

        number = getString(&len, stdin, '\n', &isNaturalNUmber);
        if (number == NULL)
        {
            return MEMORY_ERROR;
        }
        if (!isNaturalNUmber)
        {
            printf("\nВведите натуральное число\n");
            clear();
        }
    }

    char *minimalNumber = getMinimalNumber(number);
    free(number);
    if (number == NULL)
    {
        return MEMORY_ERROR;
    }

    printf("Минимальное число, полученное перестановкой цифр: ");
    printf("%s\n", minimalNumber);

    // size_t l = 0;
    // bool f= false;
    //     char * a= getString(&l, stdin, '\n', &f);
    //     printf("%d\n", f);
}

// #include <stdio.h>
// #include <stdlib.h>

// char values[] = { 5, 4, 7, 1, 2 };

// int compare(const void *a, const void *b)
// {
//     return *(const char *)a - *(const char *)b;
// }

// char arr[] = "dbaurjvgeofx";

// printf("Unsorted: %s\n", arr);
// qsort(arr, strlen(arr), 1, compare);
// printf("Sorted: %s\n", arr);