#pragma once

#include <stdbool.h>

typedef enum DictionaryErrorCode
{
    ok,
    memoryError
} DictionaryErrorCode;

typedef struct Dictionary Dictionary;

Dictionary *createDictionary(void);
DictionaryErrorCode addElement(Dictionary *const dictionary, char *const key, char *const value, const bool copyRequired);
char *getValue(Dictionary *const dictionary, char const *const key);
bool keyCheck(Dictionary *const dictionary, char const *const key);
void deleteElement(Dictionary *const dictionary, char const *const key);
void deleteDictionary(Dictionary ** const dictionary);
