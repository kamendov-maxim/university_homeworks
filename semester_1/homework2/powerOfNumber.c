#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define INPUT_ERROR 2

float linearPowerOfNumber(int number, int power);
float fastPowerOfNumber(int number, int power);
float fastPowerOfNumberRecursivePart(int number, int power);
bool test(void);

static float linearPowerOfNumber(int number, int power)
{
    if (power == 0)
    {
        return 1;
    }

    float answer = 1;

    for (int i = 0; i < abs(power); ++i)
    {
        answer *= number;
    }

    answer = (power < 0 ? 1 / answer : answer);

    return answer;
}

static float fastPowerOfNumber(int number, int power)
{
    if (power == 0)
    {
        return 1;
    }

    if (power == 1)
    {
        return number;
    }

    bool negativePowerflag = false;
    if (power < 0)
    {
        negativePowerflag = true;
        power = abs(power);
    }

    float answer = fastPowerOfNumber(number * number, power / 2) * (power % 2 == 0 ? 1 : number);

    if (negativePowerflag)
    {
        answer = 1 / answer;
    }

    return answer;
}

static bool testCase(float *test)
{
    float number = test[0];
    float pow = test[1];
    float answer = test[2];
    return (linearPowerOfNumber(number, pow) == answer) && (fastPowerOfNumber(number, pow));
}

static bool test(void)
{
    size_t const amountOfTests = 6;
    size_t const testSize = 3;
    float tests[amountOfTests][testSize] = {{5, 2, 25},
                                            {3, 4, 81},
                                            {2, -2, 0.25},
                                            {2, -4, 0.0625},
                                            {15, 3, 3375},
                                            {4, -3, 0.015625}};

    for (size_t i = 0; i < amountOfTests; ++i)
    {
        if (!testCase(tests[i]))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    if (!test())
    {
        printf("\nSorry but it seems like the program does not work correctly\n");
        return PROGRAM_FAILED_TESTS;
    }

    printf("\nWrite your number: ");
    int number = 0;
    if (scanf("%d", &number) != 1)
    {
        printf("\nSorry but it seems like the program does not work correctly\n");
        return INPUT_ERROR;
    }

    printf("\nWrite your power: ");
    int power = 0;
    if (scanf("%d", &power) != 1)
    {
        printf("\nSorry but it seems like the program does not work correctly\n");
        return INPUT_ERROR;
    }

    float answer1 = linearPowerOfNumber(number, power);
    float answer2 = fastPowerOfNumber(number, power);

    printf("\nlinear function result of work: %f", answer1);
    printf("\nfast function result of work: %f", answer2);

    return PROGRAM_FINISHED_CORRECTLY;
}
