#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVLTree.h"
#include "../String/String.h"

typedef struct Node
{
    char *value;
    int key;
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

static int nodeBalance(Node const *const root)
{
    return root->rightChild->height - root->leftChild->height;
}

void updateHeight(Node *root)
{
    size_t leftHeight = root->leftChild->height;
    size_t rightHeight = root->rightChild->height;
    root->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

static Node *leftBigRotate(Node **root)
{
    Node *a = (*root)->rightChild;
    Node *b = a->leftChild;
    (*root)->rightChild = b;
    a->leftChild = root;
    updateHeight(root);
    updateHeight(a);
    *root = a;
}

static Node *rightBigRotate(Node **root)
{
    Node *a = (*root)->leftChild;
    Node *b = a->rightChild;
    (*root)->leftChild = b;
    a->rightChild = root;
    updateHeight(root);
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
    a->leftChild = root;
    updateHeight(*root);
    updateHeight(a);
    *root = a;
}

static void balance(Node const **const root)
{
    if (nodeBalance(*root) == 2)
    {
        if ((*root)->rightChild >= 0)
        {
            leftRotate(root);
            return;
        }
        leftBigRotate(root);
        return;
    }
    else if (nodeBalance(*root) == -2)
    {
        if ((*root)->rightChild <= 0)
        {
            rightRotate(root);
            return;
        }
        rightBigRotate(root);
        return;
    }
}

DictionaryErrorCode append(Dictionary *dictionary, int const key, char *const value, bool const copyRequired)
{
    char *valueCopy = copyString(value, copyRequired);
    if (valueCopy == NULL)
    {
        return memoryError;
    }

    Node **nodeToWriteTo = searchNode(&(dictionary->root), key);
    if (*nodeToWriteTo == NULL)
    {
        Node *newNode = (Node *)calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
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
            return;
        }
        *nodeToDelete = left;
    }
    else if (right != NULL)
    {
        *nodeToDelete = right;
    }
}

static void deleteRecursion(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("check %d\n", root == NULL);
    deleteRecursion(root->leftChild);
    deleteRecursion(root->rightChild);
    // free(root->value);
    // free(root);
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
