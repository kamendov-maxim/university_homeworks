#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum ListErrorCode
{
    ok,
    memoryError
} ListErrorCode;

typedef struct List List;

size_t count(const size_t n, const size_t m, ListErrorCode *const listErrorCode);
