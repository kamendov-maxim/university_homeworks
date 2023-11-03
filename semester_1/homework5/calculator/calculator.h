typedef enum ErrorCode
{
    OK,
    PROBLEM_WITH_STACK,
    INCORRECT_INPUT,
    EMPTY_LINE
} ErrorCode;

int calculator(const char expression[], ErrorCode *errorCode);
