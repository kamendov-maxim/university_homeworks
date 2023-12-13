#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

char *getString(size_t * const len, FILE * file, char const endOfLine, bool *isNaturalNumber);
char *copyString(char const * const string);
