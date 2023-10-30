typedef enum ErrorCode
{
    OK,
    PROBLEMWITHSTACK,
    INCORRECTINPUT,
    EMPTYLINE
} ErrorCode;

int calculator(const char expression[], ErrorCode *errorCode);
