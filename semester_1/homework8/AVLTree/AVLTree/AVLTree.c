#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVLTree.h"
#include "../String/String.h"

typedef struct Node
{
    char *value;
    char *key;
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
    size_t height;
} Node;

typedef struct Dictionary
{
    Node *root;
} Dictionary;

Dictionary *createDictionary(void)
{
    return (Dictionary *)calloc(1, sizeof(Dictionary));
}

static Node **searchNode(Node **const root, char const *const key, Node **parent)
{
    if (*root == NULL)
    {
        return root;
    }

    int cmpResult = strcmp(key, (*root)->key);

    if (cmpResult == 0)
    {
        *parent = ((*root)->parent != NULL ? (*root)->parent : NULL);
        return root;
    }

    *parent = *root;
    if (cmpResult < 0)
    {
        return searchNode(&((*root)->leftChild), key, parent);
    }
    return searchNode(&((*root)->rightChild), key, parent);
}

// static size_t getHeight(Node const * const root)
// {
//     if (root->rightChild == NULL && root->rightChild == NULL)
//     {
//         root->height = 0;
//         return;
//     }
// }

static int nodeBalance(Node const *const root)
{
    size_t rightHeight = 0;
    if (root->rightChild != NULL)
    {
        rightHeight = root->rightChild->height;
    }

    size_t leftHeight = 0;
    if (root->leftChild != NULL)
    {
        leftHeight = root->leftChild->height;
    }

    return rightHeight - leftHeight;
}

static void updateHeight(Node *root)
{
    if (root->rightChild == NULL && root->rightChild == NULL)
    {
        root->height = 0;
        return;
    }
    size_t leftHeight = (root->leftChild != NULL ? root->leftChild->height : 0);
    size_t rightHeight = (root->rightChild != NULL ? root->rightChild->height : 0);
    root->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

static void leftBigRotate(Node **root)
{
    Node *a = (*root)->rightChild;
    Node *b = a->leftChild;
    (*root)->rightChild = b;
    a->leftChild = *root;
    updateHeight(*root);
    updateHeight(a);
    *root = a;
}

static void rightBigRotate(Node **root)
{
    Node *a = (*root)->leftChild;
    Node *b = a->rightChild;
    (*root)->leftChild = b;
    a->rightChild = *root;
    updateHeight(*root);
    updateHeight(a);
    *root = a;
}

static void leftRotate(Node **root)
{
    Node *a = (*root)->leftChild;
    Node *temp = a->rightChild;
    (*root)->leftChild = temp;
    a->rightChild = *root;
    updateHeight(*root);
    updateHeight(a);
    *root = a;
}

static void rightRotate(Node **root)
{
    Node *a = (*root)->rightChild;
    Node *temp = a->leftChild;
    (*root)->rightChild = temp;
    a->leftChild = *root;
    updateHeight(*root);
    updateHeight(a);
    *root = a;
}

static void balance(Node **const root)
{
    updateHeight(*root);
    if (nodeBalance(*root) == 2)
    {
        if (nodeBalance((*root)->rightChild) >= 0)
        {
            leftRotate(root);
            return;
        }
        leftBigRotate(root);
        return;
    }
    else if (nodeBalance(*root) == -2)
    {
        if (nodeBalance((*root)->rightChild) <= 0)
        {
            rightRotate(root);
            return;
        }

        rightBigRotate(root);
        return;
    }
}

static void balanceTree(Node *node)
{
    for (Node *currentNode = node; currentNode != NULL; currentNode = currentNode->parent)
    {
        balance(&currentNode);
    }
}

DictionaryErrorCode append(Dictionary *dictionary, char *const key, char *const value, bool const copyRequired)
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

    char *keyCopy = key;
    if (copyRequired)
    {
        keyCopy = copyString(key);
        if (keyCopy == NULL)
        {
            free(valueCopy);
            return memoryError;
        }
    }

    Node *parent = NULL;

    Node **nodeToWriteTo = searchNode(&(dictionary->root), key, &parent);
    if (*nodeToWriteTo == NULL)
    {
        Node *newNode = (Node *)calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
            return memoryError;
        }
        newNode->key = keyCopy;
        newNode->parent = parent;
        *nodeToWriteTo = newNode;
    }
    (*nodeToWriteTo)->value = valueCopy;

    updateHeight(*nodeToWriteTo);


    balanceTree(*nodeToWriteTo);

    return ok;
}

static void deleteNode(Node *const nodeToDelete)
{
    free(nodeToDelete->key);
    free(nodeToDelete->value);
    free(nodeToDelete);
}

static Node *getMinNode(Node *const root)
{
    Node *currentNode = root;
    for (; currentNode->leftChild != NULL; currentNode = currentNode->leftChild)
        ;
    return currentNode;
}

void deleteElement(Dictionary *const dictionary, char *const key)
{
    Node *parent = NULL;
    Node **nodeToDelete = searchNode(&(dictionary->root), key, &parent);
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
            balanceTree(*nodeToDelete);
            return;
        }
        *nodeToDelete = left;
        balanceTree(*nodeToDelete);

        return;
    }
    else if (right != NULL)
    {
        *nodeToDelete = right;
        balanceTree(*nodeToDelete);

        return;
    }
    *nodeToDelete = NULL;
    balanceTree(*nodeToDelete);
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

char *getValue(Dictionary *const dictionary, char *const key)
{
    Node *parent = NULL;
    Node **foundNode = searchNode(&(dictionary->root), key, &parent);
    if (*foundNode == NULL)
    {
        return NULL;
    }
    return (*foundNode)->value;
}

bool keyCheck(Dictionary *const dictionary, char *const key)
{
    Node *parent = NULL;
    return *(searchNode(&(dictionary->root), key, &parent)) != NULL;
}
