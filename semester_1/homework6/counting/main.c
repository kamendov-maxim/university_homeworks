#include <stdio.h>
#include <locale.h>

#include "list/list.h"
#include "tests/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define MEMORY_ERROR 2
#define PROBLEM_WITH_LIST 3
#define INPUT_ERROR 4
#define TESTS_ARE_NOT_PASSED 5

int main(void)
{
    setlocale(LC_ALL, "Rus");

    if (!test())
    {
        printf("Простите, но программа сейчас не работает\n");
        return TESTS_ARE_NOT_PASSED;
    }

    printf("Введите n - число воинов\n");
    int n;
    if (scanf("%d", &n) != 1)
    {
        printf("Похоже, что-то пошло не так\n");
        return INPUT_ERROR;
    }

    printf("Введите m - номер убитого воина\n");
    int m;
    if (scanf("%d", &m) != 1)
    {
        printf("Похоже, что-то пошло не так\n");
        return INPUT_ERROR;
    }

    ListErrorCode listErrorCode = ok;
    int counted = count(n, m, &listErrorCode);
    if (listErrorCode != ok)
    {
        printf("Похоже, что-то пошло не так\n");
        return PROBLEM_WITH_LIST;
    }

    printf("В живых останется воин под номером %d\n", counted);
    return 0;
}
