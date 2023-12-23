#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char const *const operands = "+-*/";

typedef struct Node
{
    struct Node *rightChild;
    struct Node *leftChild;
    bool isNumber;
    float value;
    char operation;
} Node;

typedef struct ParseTree
{
    Node *root;
} ParseTree;

static Node *recursion(size_t *counter, size_t const len, char const *const expression, const bool isNumber)
{
    Node *newNode = calloc(1, sizeof(Node));
    for (; expression[*counter] == ' ' || expression[*counter] == '('; ++(*counter))
        ;
    if (newNode == NULL)
    {
        return NULL;
    }

    if (isNumber)
    {
        newNode->isNumber = true;
        newNode->value = expression[*counter] - '0';
        ++(counter);
    }
    else
    {
        for (; expression[*counter] == ' '; ++(*counter))
            ;

        newNode->operation = expression[*counter];
        ++(*counter);
        for (; expression[*counter] == ' '; ++(*counter))
            ;
        if (expression[*counter] == '(')
        {
            ++(*counter);
            newNode->leftChild = recursion(counter, len, expression, false);
            if (newNode->leftChild == NULL)
            {
                free(newNode);
                return NULL;
            }
        }
        else
        {
            newNode->leftChild = recursion(counter, len, expression, true);
            if (newNode->leftChild == NULL)
            {
                free(newNode);
                return NULL;
            }
            ++(*counter);
        }

        for (; expression[*counter] == ' '; ++(*counter))
            ;
        if (expression[*counter] == '(')
        {
            ++(*counter);

            newNode->rightChild = recursion(counter, len, expression, false);
            if (newNode->rightChild == NULL)
            {
                free(newNode);
                return NULL;
            }
        }
        else
        {
            newNode->rightChild = recursion(counter, len, expression, true);
            if (newNode->rightChild == NULL)
            {
                free(newNode);
                return NULL;
            }
            ++(*counter);
        }

        for (; expression[*counter] == ' ' || expression[*counter] == ')'; ++(*counter))
            ;
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

    size_t len = strlen(expression);
    size_t counter = 0;

    tree->root = recursion(&counter, len, expression, false);
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

static float operation(const char op, const float number1, const float number2)
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
    }
}

static float calculateRecursion(Node const *const root)
{
    if (root->isNumber)
    {
        return root->value;
    }
    return operation(root->operation, calculateRecursion(root->leftChild), calculateRecursion(root->rightChild));
}

float calculate(ParseTree const *const tree)
{
    return calculateRecursion(tree->root);
}

void deleteTree(ParseTree **const tree)
{
    deleteRecursion((*tree)->root);
    free(*tree);
    *tree = NULL;
}
