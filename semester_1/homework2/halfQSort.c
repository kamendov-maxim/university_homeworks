#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void printArray(int array[], int size);
void swap(int *firstValue, int *secondValue);
void partition(int array[], int leftElement, int rightElement);
bool test(void);
bool testSwapFunction(void);
bool testPartitionFunction(void);

int main()
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return 1;
    }

    srand(time(0));

    printf("\nEnter the size of your array: ");
    int size = 0;
    scanf("%d", &size);

    while (size <= 0)
    {
        printf("\nSize of your array should be at least 1\n");
        printf("Enter the size of your array: ");
        scanf("%d", &size);
    }

    int *array = malloc(size * sizeof(int));
    if (array == NULL)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100;
    }

    printf("\nBefore parting:\n");
    printArray(array, size);
    partition(array, 0, size);
    printf("\nAfter:\n");
    printArray(array, size);

    free(array);
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int *firstValue, int *secondValue)
{
    int buffer = *firstValue;
    *firstValue = *secondValue;
    *secondValue = buffer;
}

void partition(int array[], int leftElement, int rightElement)
{
    rightElement -= 1;
    int currentSeparator = array[leftElement];
    int i = rightElement;

    for (int j = rightElement; j > leftElement; --j)
    {
        if (array[j] >= currentSeparator)
        {
            swap(&array[i], &array[j]);
            --i;
        }
    }

    swap(&array[i], &array[leftElement]);
}

bool test(void)
{
    if (!testSwapFunction())
    {
        return false;
    }

    if (!testPartitionFunction())
    {
        return false;
    }

    return true;
}

bool testSwapFunction(void)
{
    int firstValue = 0;
    int secondValue = 1;
    swap(&firstValue, &secondValue);
    if (firstValue != 1 || secondValue != 0)
    {
        return false;
    }
    return true;
}

bool testPartitionFunction(void)
{
    int testArray1[9] = {61, 99, 60, 80, 27, 57, 35, 81, 80};
    int answerArray1[9] = {27, 57, 60, 35, 61, 99, 80, 81, 80};
    partition(testArray1, 0, 9);
    for (int i = 0; i < 9; ++i)
    {
        if (testArray1[i] != answerArray1[i])
        {
            return false;
        }
    }

    int testArray2[6] = {43, 36, 55, 60, 94, 24};
    int answerArray2[6] = {24, 36, 43, 55, 60, 94};
    partition(testArray2, 0, 6);
    for (int i = 0; i < 6; ++i)
    {
        if (testArray2[i] != answerArray2[i])
        {
            return false;
        }
    }

    int testArray3[5] = {87, 91, 53, 37, 42};
    int answerArray3[5] = {37, 42, 53, 87, 91};
    partition(testArray3, 0, 5);
    for (int i = 0; i < 5; ++i)
    {
        if (testArray3[i] != answerArray3[i])
        {
            return false;
        }
    }

    int testArray4[1] = {5};
    int answerArray4[1] = {5};
    partition(testArray4, 0, 1);
    if (testArray4[0] != answerArray4[0])
    {
        return false;
    }

    return true;
}