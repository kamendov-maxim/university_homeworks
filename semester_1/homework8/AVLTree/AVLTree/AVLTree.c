#include <stdlib.h>

#include "AVLTree.h"
#include "../String/String.h"

typedef struct Node
{
    char *key;
    char *value;
    long height;
    struct Node *rightChild;
    struct Node *leftChild;
} Node;

typedef struct Dictionary
{
    Node *root;
} Dictionary;

Dictionary *createDictionary()
{
    return calloc(1, sizeof(Dictionary));
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

void createRepresentation(Dictionary const *const dictionary)
{
    char *filename = "/Users/maks/Documents/programming/university_homeworks/semester_1/homework8/AVLTree/r.gv";
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
    system("dot -Tpng /Users/maks/Documents/programming/university_homeworks/semester_1/homework8/AVLTree/r.gv -o picture.png ; open picture.png");
}

static int getHeight(Node const *const root)
{
    return (root == NULL ? 0 : root->height);
}

static long nodeBalance(Node const *const root)
{
    
    return getHeight(root->leftChild) - getHeight(root->rightChild);
}



static void updateHeight(Node *const root)
{
    if (root == NULL)
    {
        return;
    }
    long rHeight = getHeight(root->rightChild);
    long lHeight = getHeight(root->leftChild);
    root->height = (rHeight > lHeight ? rHeight : lHeight) + 1;
}

Node *leftRotate(Node *root)
{
    Node *b = root->rightChild;
    root->rightChild = b->leftChild;
    b->leftChild = root;
    updateHeight(root);
    updateHeight(b);
    return b;
}

Node *rightRotate(Node *root)
{
    Node *b = root->leftChild;
    root->leftChild = b->rightChild;
    b->rightChild = root;
    updateHeight(root);
    updateHeight(b);
    return b;
}

Node *bigLeftRotate(Node *root)
{
    Node *b = root->rightChild;
    Node *c = b->leftChild;
    b->leftChild = c->rightChild;
    root->rightChild = c->leftChild;
    c->rightChild = b;
    c->leftChild = root;
    updateHeight(root);
    updateHeight(b);
    updateHeight(c);
    return c;
}

Node *bigRightRotate(Node *root)
{
    Node *b = root->leftChild;
    Node *c = b->rightChild;
    b->rightChild = c->leftChild;
    root->leftChild = c->rightChild;
    c->leftChild = b;
    c->rightChild = root;
    updateHeight(root);
    updateHeight(b);
    updateHeight(c);
    return c;
}

static Node *balance(Node *root)
{
    // updateHeight(root);
    long nb = nodeBalance(root);
    if (nb == 2)
    {
        if (nodeBalance(root->leftChild) >= 0)
        {
            return rightRotate(root);
        }
        return bigRightRotate(root);
    }
    else if (nb == -2)
    {
        if (nodeBalance(root->rightChild) <= 0)
        {
            return leftRotate(root);
        }
        return bigLeftRotate(root);
    }

    return root;
}

static Node *insert(Node *root, char *const key, char *const value)
{
    if (root == NULL)
    {
        Node *newNode = calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
            return NULL;
        }
        newNode->key = key;
        newNode->value = value;
        updateHeight(newNode);
        return newNode;
    }

    int comparison = strcmp(root->key, key);

    if (comparison == 0)
    {
        free(key);
        free(root->value);
        root->value = value;
    }
    else if (comparison < 0)
    {
        Node *child = insert(root->rightChild, key, value);
        if (child == NULL)
        {
            return NULL;
        }
        root->rightChild = child;
        updateHeight(root);
    }
    else
    {
        Node *child = insert(root->leftChild, key, value);
        if (child == NULL)
        {
            return NULL;
        }
        root->leftChild = child;
        updateHeight(root);
    }

    return balance(root);
}

DictionaryErrorCode addElement(Dictionary *const dictionary, char *const key, char *const value, const bool copyRequired)
{
    char *keyCopy = key;
    if (copyRequired)
    {
        keyCopy = copyString(key);
        if (keyCopy == NULL)
        {
            return memoryError;
        }
    }

    char *valueCopy = value;
    if (copyRequired)
    {
        valueCopy = copyString(value);
        if (valueCopy == NULL)
        {
            free(keyCopy);
            return memoryError;
        }
    }
    Node *newRoot = insert(dictionary->root, keyCopy, valueCopy);
    if (newRoot == NULL)
    {
        free(valueCopy);
        free(keyCopy);
        return memoryError;
    }

    dictionary->root = newRoot;

    return ok;
}
