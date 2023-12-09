#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "phoneBook.h"
#include "../String/String.h"

#define DIRECTORY_LENGTH 100

typedef struct Entry
{
    char *name;
    char *number;
} Entry;

typedef struct PhoneBook
{
    Entry **entries;
    size_t firstEmptyEntry;
} PhoneBook;

PhoneBook *createPhoneBook(void)
{
    setlocale(LC_ALL, "Rus");
    PhoneBook *phoneBook = calloc(1, sizeof(PhoneBook));
    if (phoneBook == NULL)
    {
        return NULL;
    }

    Entry **entries = calloc(DIRECTORY_LENGTH, sizeof(Entry *));
    if (entries == NULL)
    {
        free(phoneBook);
        return NULL;
    }
    phoneBook->entries = entries;
    phoneBook->firstEmptyEntry = 0;
    return phoneBook;
}

void printPhoneBook(PhoneBook *phoneBook)
{
    for (size_t i = 0; i < phoneBook->firstEmptyEntry; ++i)
    {
        Entry *currentEntry = phoneBook->entries[i];
        printf("%s %s\n", currentEntry->name, currentEntry->number);
    }
}

ErrorCode addEntry(PhoneBook *phoneBook, char *const name, char *const number, const bool copyRecuired)
{
    char *nameCopy = name;
    if (copyRecuired)
    {
        nameCopy = copyString(name);
        if (nameCopy == NULL)
        {
            return memoryError;
        }
    }

    // printf("%s\n", number);
    char *numberCopy = number;
    if (copyRecuired)
    {
        numberCopy = copyString(number);
        if (numberCopy == NULL)
        {
            free(numberCopy);
            return memoryError;
        }
    }

    // printf("3 %s %s\n", nameCopy, numberCopy);

    Entry *newEntry = calloc(1, sizeof(Entry));
    if (newEntry == NULL)
    {
        free(nameCopy);
        free(numberCopy);
        return memoryError;
    }

    newEntry->name = nameCopy;
    newEntry->number = numberCopy;
    phoneBook->entries[phoneBook->firstEmptyEntry] = newEntry;
    ++phoneBook->firstEmptyEntry;
    return ok;
}

char *findNumberByName(PhoneBook const *const phoneBook, char const *const name)
{
    for (size_t i = 0; i < phoneBook->firstEmptyEntry; ++i)
    {
        if (strcmp(name, phoneBook->entries[i]->name) == 0)
        {
            return phoneBook->entries[i]->number;
        }
    }
    return NULL;
}

char *findNameByNumber(PhoneBook const *const phoneBook, char const *const number)
{
    for (size_t i = 0; i < phoneBook->firstEmptyEntry; ++i)
    {
        if (strcmp(number, phoneBook->entries[i]->number) == 0)
        {
            return phoneBook->entries[i]->name;
        }
    }
    return NULL;
}

void deletePhoneBook(PhoneBook *const phoneBook)
{
    for (size_t i = 0; i < phoneBook->firstEmptyEntry; ++i)
    {
        Entry *currentEntry = phoneBook->entries[i];
        free(currentEntry->name);
        free(currentEntry->number);
        free(currentEntry);
    }
    free(phoneBook);
}

ErrorCode readFromDataBase(PhoneBook *phoneBook, char const *const fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        return readingFileError;
    }

    size_t entriesNumber = 0;
    if (fscanf(file, "%lu\n", &entriesNumber) != 1)
    {
        fclose(file);
        return readingFileError;
    }

    ErrorCode errorCode = ok;
    size_t len = 0;
    for (size_t i = 0; i < entriesNumber; ++i)
    {
        char *name = getString(&len, file, ' ');
        if (name == NULL)
        {
            fclose(file);
            return memoryError;
        }

        char *number = getString(&len, file, '\n');
        if (number == NULL)
        {
            free(name);
            fclose(file);
            return memoryError;
        }
        errorCode = addEntry(phoneBook, name, number, false);
    }
    return ok;
}

ErrorCode saveToDataBase(PhoneBook *phoneBook, char const *const fileName)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        deletePhoneBook(phoneBook);
        return readingFileError;
    }

    fprintf(file, "%lu\n", phoneBook->firstEmptyEntry);
    for (size_t i = 0; i < phoneBook->firstEmptyEntry; ++i)
    {
        Entry *entry = phoneBook->entries[i];
        fprintf(file, "%s %s\n", entry->name, entry->number);
    }

    fclose(file);
    return ok;
}
