#include <stdio.h>
#include <locale.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2

int main(int, char **)
{
    setlocale(LC_ALL, "Russian");

    // if (!test())
    // {
    //     printf("Программа не работает\n");
    //     return PROGRAM_FAILED_TESTS;
    // }
    
}
