#pragma once

typedef struct ParseTree ParseTree;

ParseTree *createTree(char const *const expression);
float calculate(ParseTree const *const tree);
void deleteTree(ParseTree **const tree);

