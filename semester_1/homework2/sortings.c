#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define COUNTING_SORT_ARRAY_ERROR 3
#define BUBBLE_SORT_ARRAY_ERROR 4
#define INPUT_ERROR 5

#define SOMETHING_WENT_WRONG_MESSAGE "\nSorry but something went wrong\n"

void bubbleSort(int *const array, const size_t size);
int countingSort(int array[], int size);
bool test(void);
bool checkIfArrayIsSorted(int array[], int size);
bool testBubbleSort(void);
bool testCountingSort(void);
void printArray(int array[], int size);

int main()
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return PROGRAM_FAILED_TESTS;
    }

    size_t size = 0;
    while (size == 0)
    {
        printf("Enter the size of your array: ");
        scanf("%zd", &size);
        if (scanf("%zd", &size) != 1)
        {
            return INPUT_ERROR;
        }
        if (size == 0)
        {
            printf("\nSize of your array should be at least 1\n");
        }
    }

    int *countingSortArray = (int *)malloc(size * sizeof(int));
    if (countingSortArray == NULL)
    {
        printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
        return MEMORY_ERROR;
    }

    int *bubbleSortArray = (int *)malloc(size * sizeof(int));
    if (bubbleSortArray == NULL)
    {
        printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
        free(countingSortArray);
        return 1;
    }

    int currentElement = 0;
    for (int i = 0; i < size; ++i)
    {
        printf("Enter the element number %d: ", i + 1);
        scanf("%d", &currentElement);
        countingSortArray[i] = currentElement;
        bubbleSortArray[i] = currentElement;
    }

    int errorCode = countingSort(countingSortArray, size);

    if (errorCode == 1)
    {
        printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
        free(bubbleSortArray);
        free(countingSortArray);
        return COUNTING_SORT_ARRAY_ERROR;
    }

    bubbleSort(bubbleSortArray, size);

    printf("\nResult of work of counting sort: \n");
    printArray(countingSortArray, size);

    printf("\nResult of work of bubble sort: \n");
    printArray(bubbleSortArray, size);

    printf("\n");

    free(bubbleSortArray);
    free(countingSortArray);

    return PROGRAM_FINISHED_CORRECTLY;
}

void bubbleSort(int *const array, const size_t size)
{
    if (size == 0)
    {
        return;
    }

    int buffer;
    int i = 0;
    bool alreadySwapped = false;

    do
    {
        alreadySwapped = false;

        for (int j = 0; j < size - 1 - i; ++j)
        {
            if (array[j] > array[j + 1])
            {
                buffer = array[j];
                array[j] = array[j + 1];
                array[j + 1] = buffer;
                alreadySwapped = true;
            }
        }

        ++i;

    } while (alreadySwapped);
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int countingSort(int array[], int size)
{
    if (size < 0)
    {
        return 2;
    }

    if (size == 0)
    {
        return 0;
    }

    int maxElement = array[0];
    for (int i = 0; i < size; ++i)
    {
        if (array[i] > maxElement)
        {
            maxElement = array[i];
        }
    }

    int *countArray = malloc(maxElement * sizeof(int));
    if (countArray == NULL)
    {
        return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        ++countArray[array[i]];
    }

    for (int i = 1; i < maxElement; ++i)
    {
        countArray[i] += countArray[i - 1];
    }

    for (int i = maxElement; i > 0; --i)
    {
        countArray[i] = countArray[i - 1];
    }
    countArray[0] = 0;

    int *outputArray = malloc(size * sizeof(int));
    if (outputArray == NULL)
    {
        free(countArray);
        return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        outputArray[countArray[array[i]]] = array[i];
        ++countArray[array[i]];
    }

    for (int i = 0; i < size; ++i)
    {
        array[i] = outputArray[i];
    }

    free(countArray);
    free(outputArray);
    return 0;
}

bool checkIfArrayIsSorted(int array[], int size)
{
    int previousElement = array[0];
    for (int i = 1; i < size; ++i)
    {
        if (previousElement > array[i])
        {
            return false;
        }
    }
    return true;
}

bool test()
{
    if (!testBubbleSort())
    {
        return false;
    }

    if (!testCountingSort())
    {
        return false;
    }

    return true;
}

bool testBubbleSort(void)
{
    int testArray1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bubbleSort(testArray1, 10);
    if (!checkIfArrayIsSorted(testArray1, 10))
    {
        return false;
    }

    int testArray2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    bubbleSort(testArray2, 10);
    if (!checkIfArrayIsSorted(testArray2, 10))
    {
        return false;
    }

    int testArray3[10] = {4, 8, 2, 3, 1, 9, 7, 5, 10, 6};
    bubbleSort(testArray3, 10);
    if (!checkIfArrayIsSorted(testArray3, 10))
    {
        return false;
    }

    int testArray4[10] = {0};
    bubbleSort(testArray4, 10);
    if (!checkIfArrayIsSorted(testArray4, 10))
    {
        return false;
    }

    return true;
}

bool testCountingSort(void)
{
    int testArray1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int errorCode1 = countingSort(testArray1, 10);
    if (errorCode1 != 0 || !checkIfArrayIsSorted(testArray1, 10))
    {
        return false;
    }

    int testArray2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int errorCode2 = countingSort(testArray2, 10);
    if (errorCode2 != 0 || !checkIfArrayIsSorted(testArray2, 10))
    {
        return false;
    }

    int testArray3[10] = {4, 8, 2, 3, 1, 9, 7, 5, 10, 6};
    int errorCode3 = countingSort(testArray3, 10);
    if (errorCode3 != 0 || !checkIfArrayIsSorted(testArray3, 10))
    {
        return false;
    }

    int testArray4[10] = {0};
    int errorCode4 = countingSort(testArray4, 10);
    if (errorCode4 != 0 || !checkIfArrayIsSorted(testArray4, 10))
    {
        return false;
    }

    int testArray5[1] = {1};
    int errorCode5 = countingSort(testArray5, -1);
    if (errorCode5 != 2)
    {
        return false;
    }

    return true;
}
