#include "list.h"

typedef struct Node
{
    struct Node *next;
    struct Node *previous;
    char *value;
} Node;


typedef struct List
{
    Node *root;
} List;

ListErrorCode append(List * const list, char * const value, const bool copyRecuired)
{

}