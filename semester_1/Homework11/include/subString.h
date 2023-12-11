#pragma once

typedef enum ErrorCode
{
    ok,
    memoryError
} ErrorCode;

size_t findSubstring(char const *const pattern, char const *const text, ErrorCode *const errorCode);
