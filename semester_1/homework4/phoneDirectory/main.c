#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

#define STR_LENGTH 100
#define DIRECTORY_LENGTH 50

typedef struct
{
    char name[STR_LENGTH];
    char number[STR_LENGTH];
} phoneBookEntry;

int readFromDataBase(const char *fileName, phoneBookEntry entry[]);
int saveToDataBase(const char *fileName, phoneBookEntry entry[], int accountAmount);
void printOptions(void);
void printCurrentData(phoneBookEntry entry[], int accountAmount);
int addAccount(phoneBookEntry entry[], int *accountAmount);
int findNumberByName(phoneBookEntry entry[], const char name[], int accountAmount, char number[]);
int findNameByNumber(phoneBookEntry entry[], const char number[], int accountAmount, char name[]);

bool test(void);
bool testFindNameByNumber(void);
bool testFindNumberByName(void);

int main()
{
    setlocale(LC_ALL, "utf-8");

    if (!test())
    {
        printf("К сожалению, сейчас программа не работает");
        return 1;
    }

    phoneBookEntry entry[DIRECTORY_LENGTH];

    printOptions();

    int accountAmount = readFromDataBase("file.txt", entry);

    char input = '-';

    while (input != '0')
    {

        int scanned = scanf("%c", &input);
        if (scanned != 1)
        {
            printf("Ошибка\n");
            return 1;
        }

        switch (input)
        {

        case '0':
        {
            printf("Выход\n\n");
            break;
        }

        case '1':
        {
            int errorCode = addAccount(entry, &accountAmount);
            if (errorCode != 0)
            {
                printf("Ошибка\n");
            }
            printf("Новый контакт успешно добавлен\n");
            break;
        }

        case '2':
        {
            printCurrentData(entry, accountAmount);
            break;
        }

        case '3':
        {
            printf("Введите имя контакта, номер которого вы хотите узнать\n");
            char name[STR_LENGTH] = {'\0'};
            int scanned = scanf("%s", name);
            if (scanned != 1)
            {
                printf("Ошибка\n");
            }
            char number[STR_LENGTH] = {'0'};
            int errorCode = findNumberByName(entry, name, accountAmount, number);
            switch (errorCode)
            {
            case 2:
                printf("Контакт с таким именем не найден\n");
                break;
            case 0:
                printf("Номер контакта %s - %s\n", name, number);
                break;

            default:
                printf("Ошибка\n");
                break;
            }

            break;
        }

        case '4':
        {
            printf("Введите номер, владельца которого вы хотите узнать\n");
            char number[STR_LENGTH] = {'\0'};
            int scanned = scanf("%s", number);
            if (scanned != 1)
            {
                printf("Ошибка\n");
            }
            char name[STR_LENGTH] = {'0'};
            int errorCode = findNameByNumber(entry, number, accountAmount, name);
            switch (errorCode)
            {
            case 2:
                printf("Контакт с таким номером не найден\n");
                break;
            case 0:
                printf("Номер %s принадлежит контакту %s\n", number, name);
                break;

            default:
                printf("Ошибка\n");
                break;
            }

            break;
        }

        case '5':
        {
            int errorCode = saveToDataBase("file.txt", entry, accountAmount);
            if (errorCode != 0)
            {
                printf("Ошибка\n");
                return 1;
            }
            printf("Данные успешно сохранены\n");
            break;
        }
        case '\n':
        {
            printf("\n\n\nВведите цифру от 0 до 5\n");
            continue;
        }

        default:
        {
            printf("\nВы должны ввести цифру от 0 до 5\n");
            break;
        }
        }
    }

    return 0;
}

void printOptions(void)
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

int readFromDataBase(const char *fileName, phoneBookEntry entry[])
{
    FILE *file = fopen(fileName, "r");
    char newName[STR_LENGTH];
    char newNumber[STR_LENGTH];
    int i = 0;
    while (fscanf(file, "%s", newName) != EOF && fscanf(file, "%s", newNumber) != EOF)
    {
        strcpy(entry[i].name, newName);
        strcpy(entry[i].number, newNumber);
        ++i;
    }
    fclose(file);
    return i;
}

int saveToDataBase(const char *fileName, phoneBookEntry entry[], int accountAmount)
{
    FILE *file = fopen(fileName, "w");

    for (int i = 0; i < accountAmount; ++i)
    {
        fprintf(file, "%s %s\n", entry[i].name, entry[i].number);
    }

    fclose(file);
    return 0;
}

int addAccount(phoneBookEntry entry[], int *accountAmount)
{
    if (*accountAmount < DIRECTORY_LENGTH - 1)
    {
        phoneBookEntry newAccount = {{'\0'}, {'\0'}};
        char newName[STR_LENGTH] = {'\0'};
        char newNumber[STR_LENGTH] = {'\0'};

        printf("Имя нового контакта: ");
        scanf("%s", newName);
        strcpy(newAccount.name, newName);

        printf("Номер нового контакта: ");
        scanf("%s", newNumber);
        strcpy(newAccount.number, newNumber);

        entry[*accountAmount] = newAccount;
        ++(*accountAmount);
    }
    return 0;
}

int findNumberByName(phoneBookEntry entry[], const char name[], int accountAmount, char number[])
{
    for (int i = 0; i < accountAmount; ++i)
    {
        if (strcmp(name, entry[i].name) == 0)
        {
            strcpy(number, entry[i].number);
            return 0;
        }
    }
    return 2;
}

int findNameByNumber(phoneBookEntry entry[], const char number[], int accountAmount, char name[])
{
    for (int i = 0; i < accountAmount; ++i)
    {
        if (strcmp(number, entry[i].number) == 0)
        {
            strcpy(name, entry[i].name);
            return 0;
        }
    }
    return 2;
}

void printCurrentData(phoneBookEntry entry[], int accountAmount)
{
    printf("Список абонентов:\n");
    for (int i = 0; i < accountAmount; ++i)
    {
        printf("%s - %s\n", entry[i].name, entry[i].number);
    }
    printf("\n");
}

bool test(void)
{
    if (!(testFindNameByNumber() * testFindNumberByName()))
    {
        return false;
    }

    return true;
}

bool testFindNameByNumber(void)
{
    phoneBookEntry testEntry[3] = {{"Петя", "2342"}, {"Вася", "89075089911"}, {"Коля", "89117089923"}};
    int accountAmount = 3;

    char testName1[STR_LENGTH] = {'\0'};
    char testNumber1[STR_LENGTH] = "2342";
    int errorCode1 = findNameByNumber(testEntry, testNumber1, accountAmount, testName1);
    if (errorCode1 != 0)
    {
        return false;
    }
    if (strcmp("Петя", testName1) != 0)
    {
        return false;
    }

    char testName2[STR_LENGTH] = {'\0'};
    char testNumber2[STR_LENGTH] = "1212";
    int errorCode2 = findNameByNumber(testEntry, testNumber2, accountAmount, testName2);
    if (errorCode2 != 2)
    {
        return false;
    }

    return true;
}

bool testFindNumberByName(void)
{
    phoneBookEntry testEntry[3] = {{"Петя", "2342"}, {"Вася", "89075089911"}, {"Коля", "89117089923"}};
    int accountAmount = 3;

    char testName1[STR_LENGTH] = "Коля";
    char testNumber1[STR_LENGTH] = {'\0'};
    int errorCode1 = findNumberByName(testEntry, testName1, accountAmount, testNumber1);
    if (errorCode1 != 0)
    {
        return false;
    }
    if (strcmp("89117089923", testNumber1) != 0)
    {
        return false;
    }

    char testName2[STR_LENGTH] = "Лeша";
    char testNumber2[STR_LENGTH] = {'\0'};
    int errorCode2 = findNumberByName(testEntry, testName2, accountAmount, testNumber2);
    if (errorCode2 != 2)
    {
        return false;
    }

    return true;
}
