#pragma once

#include "../Stack/Stack.h"

typedef enum CalculatorErrorCode 
{
    ok,
    memoryError,
    algorithmWorkError,
    zeroDivisionError,
    wrongOperationError
} CalculatorErrorCode;

float calculator(const char *const expression, CalculatorErrorCode * const calculatorErrorCode);
