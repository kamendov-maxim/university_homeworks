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

typedef enum SortingErrorCode
{
    ok,
    memoryError
} SortingErrorCode;

void bubbleSort(int *const array, const size_t size);
SortingErrorCode countingSort(int array[], const size_t size);
bool test(void);
bool checkIfArrayIsSorted(int const *const array, size_t size);
bool testBubbleSort(void);
bool testCountingSort(void);
void printArray(int const *const array, const size_t size);

void bubbleSort(int *const array, const size_t size)
{
    if (size == 0)
    {
        return;
    }

    int buffer;
    size_t i = 0;
    bool alreadySwapped = false;

    do
    {
        alreadySwapped = false;

        for (size_t j = 0; j < size - 1 - i; ++j)
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

void printArray(int const *const array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

SortingErrorCode countingSort(int *const array, const size_t size)
{
    if (size == 0)
    {
        return ok;
    }

    int maxElement = array[0];
    for (size_t i = 0; i < size; ++i)
    {
        if (array[i] > maxElement)
        {
            maxElement = array[i];
        }
    }

    int *countArray = malloc(maxElement * sizeof(int));
    if (countArray == NULL)
    {
        return memoryError;
    }

    for (size_t i = 0; i < size; ++i)
    {
        ++countArray[array[i]];
    }

    for (size_t i = 1; i < maxElement; ++i)
    {
        countArray[i] += countArray[i - 1];
    }

    for (size_t i = maxElement; i > 0; --i)
    {
        countArray[i] = countArray[i - 1];
    }
    countArray[0] = 0;

    for (size_t i = 0; i < size; ++i)
    {
        int temp = array[i];
        array[countArray[array[i]]] = array[i];
        ++countArray[temp];
    }

    free(countArray);
    return ok;
}

bool checkIfArrayIsSorted(int const *const array, size_t size)
{
    int previousElement = array[0];
    for (size_t i = 1; i < size; ++i)
    {
        if (previousElement > array[i])
        {
            return false;
        }
    }
    return true;
}

static const bool testCase(int *const testArray, void * (*sortingFunction)(int *const, const size_t), const size_t testArraySize)
{
    int *tempArray = (int *)malloc(testArraySize);
    if (tempArray == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < testArraySize; ++i)
    {
        tempArray[i] = testArray[i];
    }

    if (sortingFunction(tempArray, testArraySize) == ok)
    {
        return false;
    }

    const bool answer = checkIfArrayIsSorted(tempArray, testArraySize);
    free(tempArray);
    return answer;
}

bool test(void)
{
    const size_t amountOfTests = 10;
    const size_t testArraySize = 10;
    int tests[amountOfTests][testArraySize] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {4, 8, 2, 3, 1, 9, 7, 5, 10, 6},
        {0}};

    for (size_t i = 0; i < amountOfTests; ++i)
    {
        if (!(testCase(tests[i], bubbleSort, testArraySize) && testCase(tests[i], countingSort, testArraySize)))
        {
            return false;
        }
    }
    return true;
}

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
