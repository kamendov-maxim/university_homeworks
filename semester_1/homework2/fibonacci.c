#include <stdio.h>
#include <stdbool.h>

int iterativeFibonacci(int number, long long int *answer);
int recursiveFibonacci(int number, long long int *answer);
long long int recursiveFibonacciBody(int number);
bool correctInputCheckForRecursiveFunction(int number);
bool testIterativeFunction(void);
bool testRecursiveFunction(void);
bool test(void);

int main()
{

    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return 1;
    }

    printf("\nEnter the number of fbonacci number you want to see: ");
    int number = 0;
    int scanfNumberOfElements = scanf("%d", &number);

    if (scanfNumberOfElements != 1)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    long long int iterativeAnswer = 0;
    int errorCode1 = iterativeFibonacci(number, &iterativeAnswer);
    if (errorCode1 != 0)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    long long int recursiveAnswer = 0;
    int errorCode2 = recursiveFibonacci(number, &recursiveAnswer);
    if (errorCode2 != 0)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    if (iterativeAnswer != recursiveAnswer)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    printf("\nResult of work of iterative function: %lld", iterativeAnswer);
    printf("\nResult of work of recursive function: %lld\n", recursiveAnswer);

    return 0;
}

int iterativeFibonacci(int number, long long int *answer)
{
    if (number < 1)
    {
        *answer = -1;
        return 1;
    }

    long long int currentNumbers[3] = {1, 1, 2};

    if (number < 4)
    {
        *answer = currentNumbers[number - 1];
        return 0;
    }

    for (int n = 2; n <= number; ++n)
    {
        currentNumbers[2] = currentNumbers[1] + currentNumbers[0];
        currentNumbers[0] = currentNumbers[1];
        currentNumbers[1] = currentNumbers[2];
    }

    *answer = currentNumbers[0];
    return 0;
}

int recursiveFibonacci(int number, long long int *answer)
{
    if (!correctInputCheckForRecursiveFunction(number))
    {
        return 1;
    }

    *answer = recursiveFibonacciBody(number);

    return 0;
}

long long int recursiveFibonacciBody(int number)
{
    if (number == 0)
    {
        return 0;
    }
    if (number == 1)
    {
        return 1;
    }
    return recursiveFibonacciBody(number - 1) + recursiveFibonacciBody(number - 2);
}

bool correctInputCheckForRecursiveFunction(int number)
{
    if (number < 1)
    {
        return false;
    }
    return true;
}

bool testIterativeFunction(void)
{
    long long int test1 = 0;
    int errorCode1 = iterativeFibonacci(-5, &test1);
    if (errorCode1 != 1)
    {
        return false;
    }

    long long int test2 = 0;
    int errorCode2 = iterativeFibonacci(3, &test2);
    if (test2 != 2 || errorCode2 != 0)
    {
        return false;
    }

    long long int test3 = 0;
    int errorCode3 = iterativeFibonacci(21, &test3);
    if (test3 != 10946 || errorCode3 != 0)
    {
        return false;
    }
    return true;
}

bool testRecursiveFunction(void)
{
    long long int test1 = 0;
    int errorCode1 = recursiveFibonacci(-5, &test1);
    if (errorCode1 != 1)
    {
        return false;
    }

    long long int test2 = 0;
    int errorCode2 = recursiveFibonacci(3, &test2);
    if (test2 != 2 || errorCode2 != 0)
    {
        return false;
    }

    long long int test3 = 0;
    int errorCode3 = recursiveFibonacci(21, &test3);
    if (test3 != 10946 || errorCode3 != 0)
    {
        return false;
    }
    return true;
}

bool test(void)
{
    if (!testIterativeFunction())
    {
        return false;
    }

    if (!testRecursiveFunction())
    {
        return false;
    }

    return true;
}