#pragma once
#include <stdbool.h>

typedef struct ParseTree ParseTree;

ParseTree *createTree(char const *const expression);
float calculate(ParseTree const *const tree, bool * const wrongOperation);
void deleteTree(ParseTree **const tree);
