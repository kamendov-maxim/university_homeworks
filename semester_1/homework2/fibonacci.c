#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool checkIfNumberIsCorrect(int n)
{
    if (n < 1)
    {
        return false;
    }
    return true;
}

int iterativeFibonacci(int number)
{

    if (number <= 3)
    {
        int firstThreeNumbers[3] = {1, 1, 2};
        return firstThreeNumbers[number - 1];
    }

    int previousNumber = 1;
    int previousNumberForPreviousNumber = 1;
    int currentNumber = 1;
    int buffer = 0;

    for (int i = 2; i < number; i++)
    {
        previousNumberForPreviousNumber = previousNumber;
        previousNumber = currentNumber;
        currentNumber = previousNumber + previousNumberForPreviousNumber;
    }

    return currentNumber;
}

int recursiveFibonacci(int number)
{

    if (number == 0)
    {
        return 0;
    }

    if (number == 1)
    {
        return 1;
    }

    return recursiveFibonacci(number - 2) + recursiveFibonacci(number - 1);
}

int timeComparison()
{
    float recursiveFunctionTimeOfWork = 1;
    float iterativeFunctionTimeOfWork = 1;
    int i = 1;
    while (recursiveFunctionTimeOfWork / iterativeFunctionTimeOfWork < 2.0)
    {

        float startTimeOfWorkIterative, finishTimeOfWorkIterative;
        startTimeOfWorkIterative = clock();
        int iterativeFunctionWorkResult = iterativeFibonacci(i);
        finishTimeOfWorkIterative = clock();
        iterativeFunctionTimeOfWork = finishTimeOfWorkIterative - startTimeOfWorkIterative;

        float startTimeOfWorkRecursive, finishTimeOfWorkRecursive;
        startTimeOfWorkRecursive = clock();
        int recursiveFunctionWorkResult = recursiveFibonacci(i);
        finishTimeOfWorkRecursive = clock();
        recursiveFunctionTimeOfWork = finishTimeOfWorkRecursive - startTimeOfWorkRecursive;

        if (iterativeFunctionWorkResult != recursiveFunctionWorkResult)
        {
            printf("Different answers for same arguments");
            return 0;
        }
        printf("%f", recursiveFunctionTimeOfWork / iterativeFunctionTimeOfWork);
        
    }
    return i;
}

int main()
{

    printf("%d", timeComparison());

    return 0;
}
