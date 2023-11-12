#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *getString(size_t * const len, FILE * filename, char const endOfLine);
char *copyString(char * const string, bool const copyRequired);
