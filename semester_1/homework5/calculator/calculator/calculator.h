#pragma once

#include "../Stack/Stack.h"

typedef enum CalculatorErrorCode 
{
    ok,
    memoryError,
    algorithmWorkError
} CalculatorErrorCode;

float calculator(const char *const expression, CalculatorErrorCode *calculatorErrorCode);
