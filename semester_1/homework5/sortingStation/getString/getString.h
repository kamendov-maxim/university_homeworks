#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// получить строку из *file до разделителя endOfLine
char *getString(FILE const * const file, char const endOfLine);
