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

static Node **searchNode(Node **const root, char const *const key, Node **const parent)
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
//     re
// }

static size_t getHeight(Node const *const root)
{
    return (root != NULL ? root->height : 0);
}

static size_t nodeBalance(Node const *const root)
{
    return (root == NULL ? 0 : getHeight(root->leftChild) - getHeight(root->rightChild));
}

static void updateHeight(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->rightChild == NULL && root->rightChild == NULL)
    {
        root->height = 1;
        return;
    }

    size_t leftHeight = getHeight(root->leftChild);
    size_t rightHeight = getHeight(root->rightChild);
    root->height = (leftHeight >= rightHeight ? leftHeight : rightHeight) + 1;
}

static void leftRotate(Node **const root)
{
    Node *a = *root;
    Node *b = a->leftChild;
    a->leftChild = b->rightChild;
    b->rightChild = a;
    b->parent = a->parent;
    a->parent = b;
    *root = b;
    // updateHeight(a);
    // updateHeight(b);
}

// parent + почему то не работают повороты

static Node *rightRotate(Node *const root)
{
    Node *a = root;
    Node *b = a->rightChild;
    // Node *aParent = a->parent;
    a->rightChild = b->leftChild;
    b->leftChild = a;
    b->parent = a->parent;
    a->parent = b;
    return b;
    // **root = b;
    // updateHeight(a);
    // updateHeight(b);
}

static void leftBigRotate(Node **const root)
{
    Node *a = *root;
    Node *b = a->leftChild;
    Node *c = b->rightChild;
    b->rightChild = c->leftChild;
    a->leftChild = c->rightChild;
    c->leftChild = b;
    c->rightChild = a;
    c->parent = a->parent;
    a->parent = c;
    b->parent = c;
    *root = c;
    // updateHeight(a);
    // updateHeight(b);
    // updateHeight(c);
}

static void rightBigRotate(Node **const root)
{
    Node *a = *root;
    Node *b = a->rightChild;
    Node *c = b->leftChild;
    b->leftChild = c->rightChild;
    a->rightChild = c->leftChild;
    c->rightChild = b;
    c->leftChild = a;
    c->parent = a->parent;
    a->parent = c;
    b->parent = c;
    *root = c;
    // updateHeight(a);
    // updateHeight(b);
    // updateHeight(c);
}

// static void balanceTree(Node ** const root)
// {
//     updateHeight(*root);
//     if (nodeBalance(*root) == 2)
//     {
//         if (nodeBalance((*root)->leftChild) <= 0)
//         {
//             leftRotate(root);
//             return;
//         }
//         leftBigRotate(root);
//         return;
//     }
//     else if (nodeBalance(*root) == -2)
//     {
//         if (nodeBalance((*root)->rightChild) >= 0)
//         {
//             * root = rightRotate(*root);
//             return;
//         }
//         rightBigRotate(root);
//         return;
//     }

// }

static Node *balanceTree(Node *const root)
{
    updateHeight(root);
    if (nodeBalance(root) == 2)
    {
        if (nodeBalance((root)->leftChild) <= 0)
        {
            // leftRotate(root);
            return root;
        }
        // leftBigRotate(root);
        return root;
    }
    else if (nodeBalance(root) == -2)
    {
        if (nodeBalance(root->rightChild) >= 0)
            {
                return rightRotate(root);
            }
        rightBigRotate(root);
        return root;
    }
    return root;
}

DictionaryErrorCode append(Dictionary *const dictionary, char *const key, char *const value, bool const copyRequired)
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
            free(valueCopy);
            free(keyCopy);
            return memoryError;
        }
        newNode->key = keyCopy;
        newNode->parent = parent;
        *nodeToWriteTo = newNode;
    }
    else
    {
        free((*nodeToWriteTo)->value);
    }
    (*nodeToWriteTo)->value = valueCopy;
    updateHeight(*nodeToWriteTo);
    // for (Node **currentNode = nodeToWriteTo; *currentNode != NULL; currentNode = &((*currentNode)->parent))
    // {
    //     balanceTree(currentNode);
    //     createRepresentation(dictionary, "/Users/maks/Documents/programming/university_homeworks/semester_1/homework8/r.gv");
    // }

    // for (Node *currentNode = *nodeToWriteTo; currentNode != NULL; currentNode = currentNode->parent)
    // {
    //     balanceTree(currentNode);
    //     createRepresentation(dictionary, "/Users/maks/Documents/programming/university_homeworks/semester_1/homework8/r.gv");

    // }

     for (Node **currentNode = nodeToWriteTo; *currentNode != NULL; currentNode = &((*currentNode)->parent))
    {
        *currentNode = balanceTree(currentNode);
        createRepresentation(dictionary, "/Users/maks/Documents/programming/university_homeworks/semester_1/homework8/r.gv");
    }
    

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
            balanceTree(nodeToDelete);
            return;
        }
        *nodeToDelete = left;
        balanceTree(nodeToDelete);

        return;
    }
    else if (right != NULL)
    {
        *nodeToDelete = right;
        balanceTree(nodeToDelete);

        return;
    }
    *nodeToDelete = NULL;
    balanceTree(nodeToDelete);
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

void deleteDictionary(Dictionary *const dictionary)
{
    deleteRecursion(dictionary->root);
    free(dictionary);
}

char *getValue(Dictionary *const dictionary, char *const key)
{
    Node *parent = NULL;
    Node **foundNode = searchNode(&(dictionary->root), key, &parent);
    return (*foundNode == NULL ? NULL : (*foundNode)->value);
}

bool keyCheck(Dictionary *const dictionary, char *const key)
{
    return getValue(dictionary, key) != NULL;
}

static void recursion(Node *const root, FILE *file, int *const i)
{
    if (root->leftChild != NULL)
    {

        recursion(root->leftChild, file, i);
        fprintf(file, "    %s->%s;\n", root->value, root->leftChild->value);
    }
    else
    {
        fprintf(file, "   null%d [shape=point];\n", *i);
        fprintf(file, "    %s->null%d\n", root->value, *i);
        ++(*i);
    }

    if (root->rightChild != NULL)
    {

        recursion(root->rightChild, file, i);
        fprintf(file, "    %s->%s;\n", root->value, root->rightChild->value);
    }
    else
    {
        fprintf(file, "   null%d [shape=point];\n", *i);
        fprintf(file, "    %s->null%d\n", root->value, *i);
        ++(*i);
    }
}

void createRepresentation(Dictionary const *const dictionary, const char *const filename)
{
    FILE *file = NULL;
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("null");
        return;
    }
    printf("%s", filename);

    fprintf(file, "digraph { graph [ dpi = 300 ]; node [color=Green style=filled] ; edge [color=brown] ; \n");
    int i = 0;
    if (dictionary->root == NULL)
    {
        fprintf(file, "null;");
    }
    else
    {
        recursion(dictionary->root, file, &i);
    }
    fprintf(file, "}");
    fclose(file);
    system("dot -Tpng /Users/maks/Documents/programming/university_homeworks/semester_1/homework8/r.gv -o picture.png ; open picture.png");
}