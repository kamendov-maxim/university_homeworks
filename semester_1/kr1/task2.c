#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int bubbleSortEven(int array[], int size);
void printArray(int array[], int size);
bool testBubbleSort(void);
bool test(void);

int main()
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return 1;
    }

    int size = 0;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    while (size <= 0)
    {
        printf("\nSize of your array should be at least 1\n");
        printf("Enter the size of your array: ");
        scanf("%d", &size);
    }

    int *bubbleSortArray = malloc(size * sizeof(int));
    if (bubbleSortArray == NULL)
    {
        printf("\nSorry but the memory is not avaliable\n");
        return 1;
    }

    int currentElement = 0;
    for (int i = 0; i < size; ++i)
    {
        printf("Enter the element number %d: ", i + 1);
        scanf("%d", &currentElement);
        bubbleSortArray[i] = currentElement;
    }
    printArray(bubbleSortArray, size);
    int errorCode = bubbleSortEven(bubbleSortArray, size);

    if (errorCode == 1)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    printf("\nResult of work of bubble sort: \n");
    printArray(bubbleSortArray, size);

    printf("\n");

    return 0;
}

int bubbleSortEven(int array[], int size)
{
    if (size < 0)
    {
        return 2;
    }

    if (size == 0)
    {
        return 0;
    }

    int buffer;
    int i = 0;
    bool alreadySwapped = false;

    do
    {
        alreadySwapped = false;

        for (int j = 0; j < size - 1 - i; j += 2)
        {
            if (array[j] > array[j + 2])
            {
                buffer = array[j];
                array[j] = array[j + 2];
                array[j + 2] = buffer;
                alreadySwapped = true;
            }
        }

        i += 2;

    } while (alreadySwapped);

    return 0;
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

bool test(void)
{
    if (!testBubbleSort())
    {
        return false;
    }
    return true;
}

bool testBubbleSort(void)
{
    int testArray1[5] = {5, 4, 3, 2, 1};
    int answerArray1[5] = {1, 4, 3, 2, 5};
    int testErrorCode1 = bubbleSortEven(testArray1, 5);
    for (int i = 0; i < 5; ++i)
    {
        if (testArray1[i] != answerArray1[i])
        {
            return false;
        }
    }
    return true;
}
