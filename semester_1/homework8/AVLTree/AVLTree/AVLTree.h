#pragma once
#include <stdbool.h>

typedef struct Dictionary Dictionary;

typedef enum DictionaryErrorCode
{
    ok,
    memoryError
} DictionaryErrorCode;

Dictionary *createDictionary(void);
char *getValue(Dictionary *const dictionary, char * const key);
bool keyCheck(Dictionary *const dictionary, char * const key);
DictionaryErrorCode append(Dictionary *const dictionary, char *const key, char *const value, bool const copyRequired);
void deleteElement(Dictionary *const dictionary, char *const key);
void deleteDictionary(Dictionary * const dictionary);

void createRepresentation(Dictionary const *const dictionary, const char *const filename);
