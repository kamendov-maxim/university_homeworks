#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct Node
{
    struct Node *rightChild;
    struct Node *leftChild;
    bool isNumber;

    union value
    {
        float number;
        char operation;
    } value;

} Node;

typedef struct ParseTree
{
    Node *root;
} ParseTree;

static float parseNumber(size_t *counter, char const *const expression)
{
    float number = 0;
    int p = 1;
    int sig = 1;
    if (expression[*counter] == '-')
    {
        sig = -1;
        ++(*counter);
    }

    while (isdigit(expression[*counter]))
    {
        number *= p;
        number += expression[(*counter)++] - '0';
        p *= 10;
    }
    number *= sig;
    return number;
}

static Node *recursion(size_t *counter, char const *const expression)
{
    Node *newNode = calloc(1, sizeof(Node));
    for (; expression[*counter] == ' '; ++(*counter))
        ;
    if (newNode == NULL)
    {
        return NULL;
    }

    if (expression[*counter] == '(')
    {
        ++(*counter);
        for (; expression[*counter] == ' '; ++(*counter))
        ;
        newNode->isNumber = false;
        newNode->value.operation = expression[(*counter)++];
        newNode->leftChild = recursion(counter, expression);
        newNode->rightChild = recursion(counter, expression);
        for (; expression[*counter] == ' '; ++(*counter))
        ;
        ++(*counter);
    }
    else
    {
        newNode->isNumber = true;
        newNode->value.number = parseNumber(counter, expression);
    }

    return newNode;
}

ParseTree *createTree(char const *const expression)
{
    ParseTree *tree = calloc(1, sizeof(ParseTree));
    if (tree == NULL)
    {
        return NULL;
    }

    size_t counter = 0;

    tree->root = recursion(&counter, expression);
    if (tree->root == NULL)
    {
        free(tree);
        return NULL;
    }
    return tree;
}

static void deleteRecursion(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    deleteRecursion(root->leftChild);
    deleteRecursion(root->rightChild);
    free(root);
}

static float operation(const char op, const float number1, const float number2, bool *const wrongOperation)
{
    switch (op)
    {
    case '+':
        return number1 + number2;

    case '-':
        return number1 - number2;

    case '*':
        return number1 * number2;

    case '/':
        return number1 / number2;
    default:
        *wrongOperation = true;
    }
}

static float calculateRecursion(Node const *const root, bool *const wrongOperation)
{
    if (root->isNumber)
    {
        return root->value.number;
    }
    return operation(root->value.operation, calculateRecursion(root->leftChild, wrongOperation), calculateRecursion(root->rightChild, wrongOperation), wrongOperation);
}

float calculate(ParseTree const *const tree, bool *const wrongOperation)
{
    *wrongOperation = false;
    return calculateRecursion(tree->root, wrongOperation);
}

void deleteTree(ParseTree **const tree)
{
    deleteRecursion((*tree)->root);
    free(*tree);
    *tree = NULL;
}
