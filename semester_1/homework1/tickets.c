#include <stdio.h>

void start(void);
void createTheArray(void);
void countingAllPossibleSums(int arrayOfAllPossibleSums[28]);
int countingTheAmountOfLuckyTickets(int arrayOfAllPossibleSums[28]);

int main()
{
    start();
    return 0;
}

void start(void)
{
    int arrayOfAllPossibleSums[28] = {0};
    countingAllPossibleSums(arrayOfAllPossibleSums);
    int answerSum = countingTheAmountOfLuckyTickets(arrayOfAllPossibleSums);
    printf("The number of all possible lucky tickets is %d\n", answerSum);
}

void countingAllPossibleSums(int arrayOfAllPossibleSums[28])
{
    for (int firstNumberOfTriplet = 0; firstNumberOfTriplet < 10; firstNumberOfTriplet++)
    {
        for (int secondNumberOfTriplet = 0; secondNumberOfTriplet < 10; secondNumberOfTriplet++)
        {
            for (int thirdNumberOfTriplet = 0; thirdNumberOfTriplet < 10; thirdNumberOfTriplet++)
            {
                int currentSum = firstNumberOfTriplet + secondNumberOfTriplet + thirdNumberOfTriplet;
                arrayOfAllPossibleSums[currentSum]++;
            }
        }
    }
}

int countingTheAmountOfLuckyTickets(int arrayOfAllPossibleSums[28])
{
    int answerSum = 0;
    for (int i = 0; i < 28; i++)
    {
        int currentSum = arrayOfAllPossibleSums[i];
        answerSum += currentSum * currentSum;
    }
    return answerSum;
}