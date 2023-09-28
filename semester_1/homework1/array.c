#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void arraySwapper(int *ourArray, int leftBorder, int rightBorder);
void MNSwapper(int *ourArray, int m, int n);
bool test(void);

int main()
{
    if (!test())
    {
        printf("Sorry but the program does not work correctly\n");
        return 1;
    }

    printf("Enter the m\n");
    int m = 0;
    scanf("%d", &m);
    printf("Enter the n\n");
    int n = 0;
    scanf("%d", &n);
    if (m == n && n == 0)
    {
        printf("Your array contains zero elements\n");
        return 0;
    }
    printf("Enter the array number by number each other on different lines\n");
    int *ourArray = (int *)malloc((m + n) * sizeof(int));
    for (int i = 0; i < (n + m); ++i)
    {
        int currentNumber;
        scanf("%d", &currentNumber);
        ourArray[i] = currentNumber;
    }

    printf("\nThis is your array before the function has done it's work: \n");
    for (int i = 0; i < (n + m); ++i)
    {
        printf("%d ", ourArray[i]);
    }

    MNSwapper(ourArray, m, n);

    printf("\nAfter\n");
    for (int i = 0; i < (n + m); ++i)
    {
        printf("%d ", ourArray[i]);
    }

    free(ourArray);
    return 0;
}

void MNSwapper(int *ourArray, int m, int n)
{
    if (m == n && n == 0)
    {
        return;
    }
    arraySwapper(ourArray, 0, m - 1);
    arraySwapper(ourArray, m, m + n - 1);
}

void arraySwapper(int *ourArray, int leftBorder, int rightBorder)
{
    int leftElement = 0;
    int rightElement = 0;

    while (rightBorder - leftBorder >= 1)
    {
        leftElement = ourArray[leftBorder];
        rightElement = ourArray[rightBorder];
        ourArray[rightBorder] = leftElement;
        ourArray[leftBorder] = rightElement;

        ++leftBorder;
        rightBorder -= 1;
        ;
    }
}

bool test(void)
{
    int testArray0[7] = {1, 2, 3, 4, 5, 6, 7};
    int testLeftBorder = 0;
    int testRightBorder = 6;
    int answer0[7] = {7, 6, 5, 4, 3, 2, 1};
    arraySwapper(testArray0, testLeftBorder, testRightBorder);
    for (int i = 0; i < 7; ++i)
    {
        if (testArray0[i] != answer0[i])
        {
            return false;
        }
    }

    int testM1 = 4;
    int testN1 = 3;
    int testArray1[7] = {1, 2, 3, 4, 5, 6, 7};
    int answer1[7] = {4, 3, 2, 1, 7, 6, 5};
    MNSwapper(testArray1, testM1, testN1);
    for (int i = 0; i < 7; ++i)
    {
        if (testArray1[i] != answer1[i])
        {
            return false;
        }
    }

    int testM2 = 6;
    int testN2 = 2;
    int testArray2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int answer2[8] = {6, 5, 4, 3, 2, 1, 8, 7};
    MNSwapper(testArray2, testM2, testN2);
    for (int i = 0; i < 8; ++i)
    {
        if (testArray2[i] != answer2[i])
        {
            return false;
        }
    }

    int testM3 = 0;
    int testN3 = 0;
    int testArray3[0] = {};
    int answer3[0] = {};
    MNSwapper(testArray3, testM3, testN3);

    return true;
}