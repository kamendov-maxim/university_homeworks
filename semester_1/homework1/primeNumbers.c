#include <stdio.h>
#include <stdbool.h>

bool isNumberPrime(int number)
{
    if (number == 1)
    {
        return false;
    }
    if (number == 2 | number == 3)
    {
        return true;
    }
    int n = 0;

    if (number % 6 == 1 | number % 6 == 5)
    {
        for (int i = 2; i * i <= number; i++)
        {
            if (number % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

int main()
{
    printf("Write the number and the program will show you all the prime numbers which are less than it: ");
    int number = 0;
    scanf("%d\n", &number);
    for (int i = 1; i < (number + 1); i++)
    {
        if (isNumberPrime(i))
        {
            printf("%d\n", i);
        }
    }
}
