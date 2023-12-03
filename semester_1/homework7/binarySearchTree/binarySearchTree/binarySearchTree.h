#pragma once
#include <stdbool.h>

typedef struct Dictionary Dictionary;

typedef enum DictionaryErrorCode
{
    ok,
    memoryError
} DictionaryErrorCode;

Dictionary *createDictionary(void);
char *getValue(Dictionary *const dictionary, const int key);
bool keyCheck(Dictionary *const dictionary, const int key);
DictionaryErrorCode append(Dictionary * const dictionary, int const key, char * value, bool const copyRequired);
void deleteElement(Dictionary * const dictionary, int const key);
void deleteDictionary(Dictionary * const dictionary);
