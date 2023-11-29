#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define INPUT_ERROR 2
#define RECURSIVE_FIBONACCI_ERROR 3
#define ITERATIVE_FIBONACCI_ERROR 4
#define TIME_COMPARE_ERROR 5
#define SOMETHING_WENT_WRONG_MESSAGE "\nSorry but something went wrong\n"

int iterativeFibonacci(int number, long long int *answer);
int recursiveFibonacci(int number, long long int *answer);
double compareTimeOfWork(int (*fibonacci1)(int, long long int *), int (*fibonacci2)(int, long long int *), const int input, int *const errorCode);
bool test(void);

double compareTimeOfWork(int (*fibonacci1)(int, long long int *), int (*fibonacci2)(int, long long int *), const int input, int *const errorCode)
{
    long long answer1 = 0;
    time_t startTime1 = time(NULL);
    const int errorCode1 = fibonacci1(input, &answer1);
    time_t finishTime1 = time(NULL);
    double time1 = difftime(finishTime1, startTime1);

    long long answer2 = 0;
    time_t startTime2 = time(NULL);
    const int errorCode2 = fibonacci1(input, &answer2);
    time_t finishTime2 = time(NULL);
    double time2 = difftime(finishTime2, startTime2);

    *errorCode = ((errorCode1 != 0 || errorCode2 != 0 || answer1 != answer2) ? 1 : 0);

    return time1 - time2;
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

static long long int recursiveFibonacciBody(int number)
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

int recursiveFibonacci(int number, long long int *answer)
{
    if (number < 1)
    {
        return 1;
    }

    *answer = recursiveFibonacciBody(number);

    return 0;
}

static const bool testFibonacciFunction(int (*fibonacci)(int, long long int *))
{
    long long int test1 = 0;
    int errorCode1 = fibonacci(-5, &test1);
    if (errorCode1 != 1)
    {
        return false;
    }

    long long int test2 = 0;
    int errorCode2 = fibonacci(3, &test2);
    if (test2 != 2 || errorCode2 != 0)
    {
        return false;
    }

    long long int test3 = 0;
    int errorCode3 = fibonacci(21, &test3);
    if (test3 != 10946 || errorCode3 != 0)
    {
        return false;
    }
    return true;
}

bool test(void)
{
    return testFibonacciFunction(iterativeFibonacci) && testFibonacciFunction(iterativeFibonacci);
}

int main(void)
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return PROGRAM_FAILED_TESTS;
    }

    printf("\nEnter the number of fibonacci number you want to see: ");
    int number = 0;
    int scanned = scanf("%d", &number);

    if (scanned != 1)
    {
        printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
        return INPUT_ERROR;
    }

    long long int iterativeAnswer = 0;
    int errorCode1 = iterativeFibonacci(number, &iterativeAnswer);
    if (errorCode1 != 0)
    {
        printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
        return ITERATIVE_FIBONACCI_ERROR;
    }

    long long int recursiveAnswer = 0;
    int errorCode2 = recursiveFibonacci(number, &recursiveAnswer);
    if (errorCode2 != 0)
    {
        printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
        return 1;
    }

    printf("\nResult of work of iterative function: %lld", iterativeAnswer);
    printf("\nResult of work of recursive function: %lld\n", recursiveAnswer);

    int errorCode = 0;

    double timeCompare = 0.0;
    for (int number = 1; timeCompare == 0.0; ++number)
    {
        timeCompare = compareTimeOfWork(iterativeFibonacci, recursiveFibonacci, number, &errorCode);
        if (errorCode != 0)
        {
            printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
            return TIME_COMPARE_ERROR;
        }
        if (timeCompare < 0.0)
        {
            printf("Iterative function is significantly faster than recursive beginning with fibonacci number #%d\n", number);
        } 
    }

    return PROGRAM_FINISHED_CORRECTLY;
