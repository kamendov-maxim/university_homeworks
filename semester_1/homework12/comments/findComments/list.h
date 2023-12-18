#pragma once

#include "errorCode.h"

typedef struct List List;

List * createList(void);
ErrorCode addElement(List * list, char * const value);
char ** writeToDefaultArray(List const * const list, size_t *length);
void deleteList(List ** const list);
