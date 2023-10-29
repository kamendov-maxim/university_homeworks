

typedef enum ErrorCode
{
    OK,
    problemWithStack,
    incorrectInput,
    emptyLine
} ErrorCode;

int calculator(const char expression[], ErrorCode *errorCode);
