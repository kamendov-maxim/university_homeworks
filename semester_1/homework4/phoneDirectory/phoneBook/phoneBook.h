#pragma once

#include <stdbool.h>

typedef enum ErrorCode
{
    ok,
    memoryError,
    readingFileError
} ErrorCode;

typedef struct PhoneBook PhoneBook;

PhoneBook *createPhoneBook(void);
void printPhoneBook(PhoneBook const * const phoneBook);
ErrorCode addEntry(PhoneBook * const phoneBook, char * const name, char * const number, const bool copyRecuired);
char * findNumberByName(PhoneBook const * const phoneBook, char const * const name);
char * findNameByNumber(PhoneBook const * const phoneBook, char const * const number);
void deletePhoneBook(PhoneBook * const phoneBook);
ErrorCode readFromDataBase(PhoneBook * const phoneBook, char const *const fileName);
ErrorCode saveToDataBase(PhoneBook * const phoneBook, char const *const fileName);
