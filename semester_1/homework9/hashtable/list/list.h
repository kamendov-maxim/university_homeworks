#include <stdbool.h>

typedef enum ListErrorCode
{
    okList,
    memoryErrorList
} ListErrorCode;

typedef struct List List;

List *createList(void);
ListErrorCode append(List * const list, char * const value, const bool copyRequired);
bool checkElement(List const * const list, char const * const value);
void deleteElement(List * const list, char const * const value);
void deleteList(List * const list);
