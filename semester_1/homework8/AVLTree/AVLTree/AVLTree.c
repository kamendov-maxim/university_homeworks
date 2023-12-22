#include <stdlib.h>

#include "AVLTree.h"
#include "../String/String.h"

typedef struct Node
{
    struct Node *rightChild;
    struct Node *leftChild;

    char *key;
    char *value;
    size_t height;
    struct Node *parent;
} Node;

typedef struct Dictionary
{
    Node *root;
} Dictionary;

Dictionary *createDictionary(void)
{
    return calloc(1, sizeof(Dictionary));
}

static size_t getHeight(Node const *const root)
{
    return (root == NULL ? 0 : root->height);
}

static void updateHeight(Node *const root)
{
    if (root == NULL)
    {
        return;
    }

    size_t rHeight = getHeight(root->rightChild);
    size_t lHeight = getHeight(root->leftChild);

    root->height = (rHeight > lHeight ? rHeight : lHeight) + 1;
}

static size_t nodeBalance(Node const *const root)
{
    if (root == NULL)
    {
        return 0;
    }

    return getHeight(root->leftChild) - getHeight(root->rightChild);
}

static void leftRotate(Node **const root)
{
    Node *a = (*root);
    Node *b = a->leftChild;
    a->leftChild = b->rightChild;
    b->rightChild = a;
    b->parent = a->parent;
    a->parent = b;
    *root = b;
    updateHeight(a);
    updateHeight(b);
}

static void rightRotate(Node **const root)
{
    Node *a = (*root);
    Node *b = a->rightChild;
    a->rightChild = b->leftChild;
    b->leftChild = a;
    b->parent = a->parent;
    a->parent = b;
    *root = b;
    updateHeight(a);
    updateHeight(b);
}

static void bigLeftRotate(Node **const root)
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
    updateHeight(a);
    updateHeight(b);
    updateHeight(c);
}

static void bigRightRotate(Node **const root)
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
    updateHeight(a);
    updateHeight(b);
    updateHeight(c);
}

static void balance(Node **const root)
{
    updateHeight(*root);
    size_t nb = nodeBalance(*root);
    if (nb == 2)
    {
        if (nodeBalance((*root)->rightChild) <= 0)
        {
            leftRotate(root);
            return;
        }
        bigLeftRotate(root);
    }
    else if (nb == -2)
    {
        if (nodeBalance((*root)->leftChild) >= 0)
        {
            rightRotate(root);
            return;
        }
        bigRightRotate(root);
    }
}


// static Node * balance(Node **const root)
// {
//     updateHeight(*root);
//     size_t nb = nodeBalance(*root);
//     if (nb == 2)
//     {
//         if (nodeBalance((*root)->rightChild) <= 0)
//         {
//             leftRotate(root);
//             return *root;
//         }
//         bigLeftRotate(root);
//             return *root;

//     }
//     else if (nb == -2)
//     {
//         if (nodeBalance((*root)->leftChild) >= 0)
//         {
//             rightRotate(root);
//             return *root;
//         }
//         bigRightRotate(root);
//             return *root;

//     }
// }


// static void balanceTree(Dictionary *const dictionary, Node *startNode)
// {
//     for (Node *currentNode = startNode; currentNode != NULL; currentNode = currentNode->parent)
//     {
//         balance(&currentNode);
//         if (currentNode->parent == NULL)
//         {
//             startNode = currentNode;
//         }
//     }
//     dictionary->root = startNode;
// }

static void balanceTree(Dictionary *const dictionary, Node *startNode)
{
    // char *pNo = NULL;
    Node *pNode = NULL;
    Node *pBalancedNode = NULL;

    // Node *currentNode = startNode;
    // while (currentNode != NULL)
    // {
    //     pNode = currentNode;
    //     balance(&currentNode);
    //     pBalancedNode = (currentNode == pNode? NULL: currentNode);

    //     currentNode = currentNode->parent;
    //     if (pBalancedNode != NULL)
    //     {
    //         if (currentNode->leftChild == NULL)
    //         {
    //             currentNode->rightChild = pBalancedNode;
    //         }
    //         else if (currentNode->leftChild != pNode)
    //         {
    //             currentNode->rightChild = pBalancedNode;
    //         }
    //         else
    //         {
    //             currentNode->leftChild = pBalancedNode;
    //         }
    //         pBalancedNode = NULL; 
    //         if (currentNode->parent == NULL)
    //         {
    //             pNode = pBalancedNode;
    //         }
            
    //     }
    // }
    

    for (Node *currentNode = startNode; currentNode != NULL; currentNode = currentNode->parent)
    {
        if (pBalancedNode != NULL)
        {
            if (currentNode->leftChild != pNode)
            {
                currentNode->rightChild = pBalancedNode;
            }
            else
            {
                currentNode->leftChild = pBalancedNode;
            }
            pBalancedNode = NULL; 
            
            
        }
        
        pNode = currentNode;
        balance(&currentNode);
        // pBalancedNode = (currentNode == pNode? NULL: currentNode);
        // if (currentNode->parent == NULL)
        //     {
        //         pNode = pBalancedNode;
        //     }

        if (currentNode != pNode)
        {
            pBalancedNode = currentNode;
            if (currentNode->parent == NULL)
            {
                pNode = currentNode;
            }
        }
        
        // pKey = currentNode->key;
    }
    dictionary->root = pNode;
}

// static void balanceTree(Dictionary *const dictionary, Node ** const startNode)
// {
//     Node ** currentNodeDPtr = startNode;
//     for (Node *currentNode = *startNode; currentNode != NULL; currentNode = currentNode->parent)
//     {
//         balance(&currentNode);
//         *currentNodeDPtr = currentNode;
//         // if (currentNode->parent == NULL)
//         // {
//         //     startNode = currentNode;
//         // }

//         currentNodeDPtr = &((*currentNodeDPtr)->parent);
//     }
//     // dictionary->root = startNode;
// }

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

DictionaryErrorCode addElement(Dictionary *const dictionary, char *const key, char *const value, const bool copyRequired)
{
    char *valueCopy = value;
    if (copyRequired)
    {
        valueCopy = copyString(value);
        if (value == NULL)
        {
            return memoryError;
        }
    }

    Node *parent = NULL;
    Node **nodeToWriteTo = searchNode(&(dictionary->root), key, &parent);
    if (*nodeToWriteTo == NULL)
    {
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
        Node *newNode = calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
            free(keyCopy);
            free(valueCopy);
            return memoryError;
        }
        newNode->parent = parent;
        newNode->key = keyCopy;
        *nodeToWriteTo = newNode;
    }
    else
    {
        free((*nodeToWriteTo)->value);
    }
    (*nodeToWriteTo)->value = valueCopy;

    // Node *node = *nodeToWriteTo;
    // for (Node * currentNode = node; currentNode != NULL; currentNode = currentNode->parent)
    // {
    //     balance(&currentNode);
    //     if (currentNode->parent == NULL)
    //     {
    //         node = currentNode;
    //     }
    // }
    // dictionary->root = node;

    balanceTree(dictionary, *nodeToWriteTo);

    return ok;
}

bool keyCheck(Dictionary *const dictionary, char const *const key)
{
    return getValue(dictionary, key) != NULL;
}

char *getValue(Dictionary *const dictionary, char const *const key)
{
    Node *parent = NULL;
    Node **foundNode = searchNode(&(dictionary->root), key, &parent);
    if (*foundNode == NULL)
    {
        return NULL;
    }

    return (*foundNode)->value;
}

static void deleteNode(Node *const nodeToDelete)
{
    if (nodeToDelete != NULL)
    {
        free(nodeToDelete->value);
        free(nodeToDelete->key);
        free(nodeToDelete);
    }
}

static Node *getMinNode(Node *const root)
{
    Node *currentNode = root;
    for (; currentNode->leftChild != NULL; currentNode = currentNode->leftChild)
        ;
    return currentNode;
}

void deleteElement(Dictionary *const dictionary, char const * const key)
{
    Node * parent = NULL;
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
            *nodeToDelete = right;
            right->parent = parent;
            Node *minNode = getMinNode(right);
            minNode->leftChild = left;
            updateHeight(minNode);
            left->parent = minNode;
            balanceTree(dictionary, minNode);
            return;
        }
        *nodeToDelete = left;
        left->parent = parent;
        balanceTree(dictionary, *nodeToDelete);
        return;
    }
    else if (right != NULL)
    {
        *nodeToDelete = right;
        right->parent = parent;
        balanceTree(dictionary, *nodeToDelete);

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

    deleteRecursion(root->rightChild);
    deleteRecursion(root->leftChild);
    deleteNode(root);
}

void deleteDictionary(Dictionary **dictionary)
{
    deleteRecursion((*dictionary)->root);
    free(*dictionary);
    *dictionary = NULL;
}
