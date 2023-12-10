#include <stdio.h>
#include <stdlib.h>

#include "userInterface.h"

#define INPUT_ERROR 3
#define COMMANDS_NUMBER 6
#define ERROR_MESSAGE "Во время выполнения программы произошла ошибка\n"

static void printOptions(void)
{
    printf("\n    - - Телефонный справочник - -\n");
    printf("Нажмите 0, чтобы выйти из справочника\n");
    printf("Нажмите 1, чтобы добавить новую запись\n");
    printf("Нажмите 2, чтобы просмотреть все существующие записи\n");
    printf("Нажмите 3, чтобы найти телефон по имени абонента\n");
    printf("Нажмите 4, чтобы найти имя абонента по номеру телефона\n");
    printf("Нажмите 5, чтобы сохранить новые записи\n");
    printf("     - - - - - - - - - - - - - - - \n");
}

Command userInterface(PhoneBook *phoneBook)
{
    Command input = exitCommand;
    do
    {
        printOptions();
        if (scanf("%d", &input) != 1)
        {
            printf("%s", ERROR_MESSAGE);
            deletePhoneBook(phoneBook);
            exit(INPUT_ERROR);
        }

        if (input >= COMMANDS_NUMBER || input < 0)
        {
            printf("Введите цифру от 0 до 5\n");
        }
        
    } while (input >= COMMANDS_NUMBER || input < 0);
    return input;
}
