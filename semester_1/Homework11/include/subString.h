#pragma once

typedef enum ErrorCode
{
    ok,
    memoryError
} ErrorCode;

long findSubstring(char const *const pattern, char const *const text, ErrorCode *const errorCode);
