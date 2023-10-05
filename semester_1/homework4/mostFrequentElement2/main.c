#include "smartQuickSort.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int mostFrequentElement(int array[], int size);
void printArray(int array[], int size);

bool test(void);
bool testStarterForMostFrequentELement(int testArray[], int size, int answer);
bool testMostFrequentElementFunction(void);

int main()
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return 1;
    }

    FILE *file = fopen("file.txt", "r");
    if (file == NULL)
    {
        return 1;
    }

    int array[100] = {0};

    int i = 0;
    while (fscanf(file,"%d" , &(array[i])) != EOF)
    {
        ++i;
    }

    fclose(file);


    printf("Numbers from the file:\n");
    printArray(array, i);

    int errorCode = smartQuickSort(array, 0, i - 1);

    printf("\nThe most frequent element in the file is %d\n", mostFrequentElement(array, i + 1));
    

    
    return 0;
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int mostFrequentElement(int array[], int size)
{
    int mostFrequentElement = array[0];
    int counter = 1;
    int maxCount = 1;
    for (int i = 1; i < size; ++i)
    {
        if (array[i] == array[i - 1])
        {
            ++counter;
            if (counter > maxCount)
            {
                maxCount = counter;
                mostFrequentElement = array[i];
            }
        }
        else
        {
            counter = 1;
        }
    }
    return mostFrequentElement;
}

bool test(void)
{
    if (!(testMostFrequentElementFunction() * testSmartQuickSort()))
    {
        return false;
    }

    return true;
}

bool testMostFrequentElementFunction(void)
{
    int testArray1[10] = {1, 3, 4, 4, 5, 6, 7, 7, 7, 8};
    int answer1 = 7;

    int testArray2[4] = {3, 0, 0, 5};
    int answer2 = 0;

    int testArray3[1] = {0};
    int answer3 = 0;

    if (!(testStarterForMostFrequentELement(testArray1, 10, answer1) * testStarterForMostFrequentELement(testArray2, 4, answer2) * testStarterForMostFrequentELement(testArray3, 1, answer3)))
    {
        return false;
    }

    return true;
}

bool testStarterForMostFrequentELement(int testArray[], int size, int answer)
{
    if (mostFrequentElement(testArray, size) != answer)
    {
        return false;
    }
    return true;
}