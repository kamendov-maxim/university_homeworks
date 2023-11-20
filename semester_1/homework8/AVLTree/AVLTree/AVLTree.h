#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Dictionary Dictionary;

typedef enum DictionaryErrorCode
{
    ok,
    memoryError
} DictionaryErrorCode;

Dictionary *createDictionary(void);
char *getValue(Dictionary  *const dictionary, const int key);
bool keyCheck(Dictionary  *const dictionary, const int key);
DictionaryErrorCode append(Dictionary *dictionary, int const key, char * const value, bool const copyRequired);
void deleteElement(Dictionary *dictionary, int const key);
void deleteDictionary(Dictionary *dictionary);