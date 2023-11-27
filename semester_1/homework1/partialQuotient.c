#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define INPUT_ERROR 2

int partialQuotient(int number, int divisor);
bool test(void);

static void scanfCheck(const int scanned)
{
    if (scanned != 1)
    {
        exit(INPUT_ERROR);
    }
}

int partialQuotient(int number, int divisor)
{
    int absNumber = abs(number);
    int absDivisor = abs(divisor);

    int q = 0;
    for (; (absNumber - q * absDivisor) >= absDivisor; ++q)
        ;

    if (number < 0 ^ divisor < 0)
    {
        q += 1;
        q *= -1;
    }
    else if (number < 0 && divisor < 0)
    {
        q += 1;
    }

    return q;
}

int main(void)
{
    if (!test())
    {
        printf("Sorry nut the program does not work correctly\n");
        return PROGRAM_FAILED_TESTS;
    }

    int number = 0;
    int divisor = 0;
    while (divisor == 0)
    {
        printf("Enter the number: ");
        scanfCheck(scanf("%d", &number));
        printf("Enter the divisor: ");
        scanfCheck(scanf("%d", &divisor));
        if (divisor == 0)
        {
            printf("0 cannot be the divisor\n");
        }
    }

    printf("Your partial quotient of number %d and divisor %d is %d\n", number, divisor, partialQuotient(number, divisor));
    return 0;
}

static bool testCase(int *const testArray)
{
    int number = testArray[0];
    int divisor = testArray[1];
    int answer = testArray[2];

    return partialQuotient(number, divisor) == answer;
}

bool test(void)
{
    int testArray1[3] = {78, 33, 2};
    int testArray2[3] = {-78, 33, -3};
    int testArray3[3] = {-9, -13, 1};
    int testArray4[3] = {9, 90, 0};
    int testArray5[3] = {78, 26, 3};

    return testCase(testArray1) && testCase(testArray2) && testCase(testArray3) && testCase(testArray4) && testCase(testArray5);
}
