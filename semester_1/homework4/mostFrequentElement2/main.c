#include "smartQuickSort.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define filename "file.txt"
#define testsAreNotPassedError 1;
#define memoryAccessError 2;

int mostFrequentElement(int *array, size_t size);
void printArray(int *array, size_t size);

bool test(void);
bool testCaseForMostFrequentELement(int testArray[], int size, int answer);
bool testMostFrequentElementFunction(void);

int main(void)
{
    // if (!test())
    // {
    //     printf("\nSorry but the program does not work correctly\n");
    //     return testsAreNotPassedError;
    // }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return memoryAccessError;
    }

    size_t size = '\0';
    fscanf(file,"%zd" , &size);

    int array[100] = {0}; 

    for (int i = 0; i < size; ++i)
    {
        fscanf(file,"%d" , &array[i]);
    }

    

    
    fclose(file);


    printf("Numbers from the file:\n");
    printArray(array, size);
    printf("dasads");

    smartQuickSort(array, 0, size - 1);
    printf("sdad");

    printf("\nThe most frequent element in the file is %d\n", mostFrequentElement(array, size + 1));
    

    
    return 0;
}

void printArray(int *array, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("a");
}

int mostFrequentElement(int *array, size_t size)
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
    return testMostFrequentElementFunction() && testSmartQuickSort();
}

bool testMostFrequentElementFunction(void)
{
    int testArray1[10] = {1, 3, 4, 4, 5, 6, 7, 7, 7, 8};
    int answer1 = 7;

    int testArray2[4] = {3, 0, 0, 5};
    int answer2 = 0;

    int testArray3[1] = {0};
    int answer3 = 0;

    return testCaseForMostFrequentELement(testArray1, 10, answer1) * testCaseForMostFrequentELement(testArray2, 4, answer2) * testCaseForMostFrequentELement(testArray3, 1, answer3);
}

bool testCaseForMostFrequentELement(int testArray[], int size, int answer)
{
    return mostFrequentElement(testArray, size) != answer;
}
