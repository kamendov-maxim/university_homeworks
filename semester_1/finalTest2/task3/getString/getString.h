#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// читает строку из file до символа конца строки endOfLine
char *getString(FILE * file, char const endOfLine);
