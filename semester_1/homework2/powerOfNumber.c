#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

float linearPowerOfNumber(int number, int power);
float fastPowerOfNumber(int number, int power);
float fastPowerOfNumberRecursivePart(int number, int power);
bool test(void);

int main()
{
    if (!test())
    {
        printf("\nSorry but it seems like the program does not work correctly\n");
        return 1;
    }
    printf("\nWrite your number: ");
    int number = 0;
    int errorCodeScanf1 = scanf("%d", &number);
    if (errorCodeScanf1 != 1)
    {
        printf("\nSorry but it seems like the program does not work correctly\n");
        return 1;
    }

    printf("\nWrite your power: ");
    int power = 0;
    int errorCodeScanf2 = scanf("%d", &power);
    if (errorCodeScanf2 != 1)
    {
        printf("\nSorry but it seems like the program does not work correctly\n");
        return 1;
    }
    float answer1 = linearPowerOfNumber(number, power);
    float answer2 = fastPowerOfNumber(number, power);

    printf("\nlinear function result of work: %f", answer1);
    printf("\nfast function result of work: %f", answer2);

    return 0;
}

float linearPowerOfNumber(int number, int power)
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

    if (power < 0)
    {
        answer = 1 / answer;
    }

    return answer;
}

float fastPowerOfNumber(int number, int power)
{
    if (power == 0.0)
    {
        return 1;
    }

    if (power == 1.0)
    {

        return number;
    }

    bool negativePowerflag = false;
    if (power < 0)
    {
        negativePowerflag = true;
        power = abs(power);
    }

    float answer = fastPowerOfNumberRecursivePart(number, power);

    if (negativePowerflag)
    {
        answer = 1 / answer;
    }

    return answer;
}

float fastPowerOfNumberRecursivePart(int number, int power)
{
    if (power % 2 == 0)
    {
        return fastPowerOfNumber(number * number, power / 2);
    }
    return fastPowerOfNumber(number * number, power / 2) * number;
}

bool test(void)
{
    float numbers[5] = {3, 4, 0, -5, -9};
    float powers[4] = {0, 7, 2, 5};
    float answers[20] = {1, 2187, 9, 243, 1, 16384, 16, 1024, 1, 0, 0, 0, 1, -78125, 25, -3125, 1, -4782969, 81, -59049};
    int currentAnswer = 0;
    for (int n = 0; n < 5; ++n)
    {
        for (int p = 0; p < 4; ++p)
        {
            if (linearPowerOfNumber(numbers[n], powers[p]) != answers[currentAnswer])
            {
                return false;
            }
            if (fastPowerOfNumber(numbers[n], powers[p]) != answers[currentAnswer])
            {
                return false;
            }
            ++currentAnswer;
        }
    }
    return true;
}