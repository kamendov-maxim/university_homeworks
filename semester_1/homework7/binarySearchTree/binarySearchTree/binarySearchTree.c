#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binarySearchTree.h"
#include "../String/String.h"

typedef struct Node
{
    char *value;
    int key;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

typedef struct Dictionary
{
    Node *root;
} Dictionary;

Dictionary *createDictionary(void)
{
    return (Dictionary *)calloc(1, sizeof(Dictionary));
}

static Node **searchNode(Node **const root, const int key)
{
    if (*root == NULL)
    {
        return root;
    }

    if (key == ((*root)->key))
    {
        return root;
    }

    if (key < (*root)->key)
    {
        return searchNode(&((*root)->leftChild), key);
    }
    return searchNode((&(*root)->rightChild), key);
}

DictionaryErrorCode append(Dictionary * const dictionary, int const key, char * const value, bool const copyRequired)
{
    char *valueCopy = value;
    if (copyRequired)
    {
        valueCopy = copyString(value);
        if (valueCopy == NULL)
        {
            return memoryError;
        }
    }

    Node **nodeToWriteTo = searchNode(&(dictionary->root), key);
    if (*nodeToWriteTo == NULL)
    {
        Node *newNode = (Node *)calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
            free(valueCopy);
            return memoryError;
        }
        newNode->key = key;
        *nodeToWriteTo = newNode;
    }
    (*nodeToWriteTo)->value = valueCopy;
    return ok;
}

static void deleteNode(Node *const nodeToDelete)
{
    if (nodeToDelete != NULL)
    {
        free(nodeToDelete->value);
        free(nodeToDelete);
    }
}

static Node *getMinNode(Node *const root)
{
    Node *node = NULL;
    Node *currentNode = root;
    for (; currentNode->leftChild != NULL; currentNode = currentNode->leftChild)
    {
        if (currentNode->leftChild->leftChild == NULL)
        {
            node = currentNode->leftChild;
            currentNode->leftChild = NULL;
            return node;
        }
    }
    return currentNode;
}

void deleteElement(Dictionary *const dictionary, int const key)
{
    Node **nodeToDelete = searchNode(&(dictionary->root), key);
    if (*nodeToDelete == NULL)
    {
        return;
    }

    Node *left = (*nodeToDelete)->leftChild;
    Node *right = (*nodeToDelete)->rightChild;

    deleteNode(*nodeToDelete);

    if (left != NULL)
    {
        if (right != NULL)
        {
            *nodeToDelete = getMinNode(right);
            if (*nodeToDelete != right)
            {
                (*nodeToDelete)->rightChild = right;
            }
            (*nodeToDelete)->leftChild = left;
            return;
        }
        *nodeToDelete = left;
        return;
    }
    else if (right != NULL)
    {
        *nodeToDelete = right;
        return;
    }
    *nodeToDelete = NULL;
}

static void deleteRecursion(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    deleteRecursion(root->leftChild);
    deleteRecursion(root->rightChild);
    deleteNode(root);
}

void deleteDictionary(Dictionary *dictionary)
{
    deleteRecursion(dictionary->root);
    free(dictionary);
}

char *getValue(Dictionary *const dictionary, const int key)
{
    Node **foundNode = searchNode(&(dictionary->root), key);
    if (*foundNode == NULL)
    {
        return NULL;
    }
    return (*foundNode)->value;
}

bool keyCheck(Dictionary *const dictionary, const int key)
{
    return *(searchNode(&(dictionary->root), key)) != NULL;
}
