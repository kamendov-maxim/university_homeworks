#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int partialQuotient(int number, int divisor, int *answer);

void programStart(void);
bool correctInputCheck(int number, int divisor);

bool test(void);
bool testingPartialQuotientFunction(void);
bool testCorrectInputCheck(void);

int main()
{

    if (!test())
    {
        printf("Sorry but the program does not work correctly\n");
        return 0;
    }
    programStart();

    return 0;
}

int partialQuotient(int number, int divisor, int *resultOfWork)
{
    *resultOfWork = 0;

    if (divisor == 0)
    {
        return 1;
    }

    const int absNumber = abs(number);
    const int absDivisor = abs(divisor);
    int answer = 0;

    while (((absNumber - absDivisor * answer) >= absDivisor) || (((number < 0 && divisor > 0) ^ (number > 0 && divisor < 0)) && absNumber > answer * absDivisor))
    {
        ++answer;
    }

    if (number < 0 ^ divisor < 0)
    {
        answer *= -1;
    }
    *resultOfWork = answer;
    return 0;
}

bool correctInputCheck(int number, int divisor)
{
    if (divisor == 0)
    {
        printf("Divisor cannot be 0\n");
        return false;
    }
    return true;
}

void programStart(void)
{
    printf("Write your number: ");
    int number = 0;
    scanf("%d", &number);
    printf("Write your divisor: ");
    int divisor = 1;
    scanf("%d", &divisor);

    int answer = 0;
    int errorCode = partialQuotient(number, divisor, &answer);
    if (errorCode == 1)
    {
        printf("Divisor cannot be zero\n");
        return;
    }
    printf("Your partial quotient = %d\n", answer);
}

// testing

bool test(void)
{
    if (!testingPartialQuotientFunction())
    {
        return false;
    }

    return true;
}

bool testingPartialQuotientFunction(void)
{
    int numbersForTest[3] = {-7, -15, 10000};
    int divisorsForTest[3] = {3, -2, -1000231};
    int answers[9] = {-3, 3, 0, -5, 7, 0, 3333, -5000, -1};
    int currentAnswer = 0;
    int errorCode = 0;
    int currentTest = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {

            errorCode = partialQuotient(numbersForTest[i], divisorsForTest[j], &currentTest);
            if (errorCode == 0)
            {
                if (currentTest != answers[currentAnswer])
                {

                    return false;
                }
            }
            ++currentAnswer;
        }
    }
    return true;
}
