#include <stdio.h>
#include <stdbool.h>
#include <locale.h>


#include "../get_string/get_string.h"
#include "calculator.h"


int main()
{
    setlocale(LC_ALL, "Rus");
    if (!test())
    {
        printf("Простите, но похоже, что программа сейчас не работает корректно\n");
        return 1;
    }

    printf("Введите арифметическое выражение в постфиксной форме: ");

    size_t len = 0;
    char expression[] = get_string(&len);
    if ( expression == NULL)
    {
        printf("Ошибка доступа к памяти\n");
    }

    while (strlen(expression) < 2)
    {
        printf("\nВы не ввели выражение\nПопробуйте ещё раз\n\n");

        printf("Введите арифметическое выражение в постфиксной форме: ");

        fgets(expression, sizeof(expression), stdin);
    }

    ErrorCode errorCode = OK;
    int result = calculator(expression, &errorCode);
    if (errorCode != OK)
    {
        printf("Похоже, что-то пошло не так\n", errorCode);
        return 1;
    }
    printf("Ответ: %d", result);

    return 0;
}
