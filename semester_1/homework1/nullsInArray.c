#include <stdio.h>

int counterOfNullsInArray(int *array, int length)
{
    int counter = 0;
    for (int i = 0; i < length; i++)
    {
        if (array[i] == 0)
        {
            counter++;
        }
    }

    return counter;
}

int main()
{
    printf("Write a legth of your array: ");
    int lengthOfArray = 0;
    scanf("%d", &lengthOfArray);

    int ourArray[lengthOfArray];
    printf("Write numbers of your array one by one each other on the separate line:\n");
    for (int i = 0; i < lengthOfArray; i++)
    {
        int currentNumber = 0;
        scanf("%d", &currentNumber);
        ourArray[i] = currentNumber;
    }

    printf("\nlet's count how many zeroes it has\n");
    printf("\nYour array contains %d zeroes\n\n", counterOfNullsInArray(ourArray, lengthOfArray));

    return 0;
}
