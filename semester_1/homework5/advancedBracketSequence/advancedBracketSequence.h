#pragma once

#include <stdbool.h>

typedef enum ErrorCode
{
    OK,
    PROBLEMWITHSTACK
} ErrorCode;

bool isBalanced(const char *const line, ErrorCode *const errorCode);
