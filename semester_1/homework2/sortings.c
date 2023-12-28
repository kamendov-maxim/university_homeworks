#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define COUNTING_SORT_ARRAY_ERROR 3
#define BUBBLE_SORT_ARRAY_ERROR 4
#define INPUT_ERROR 5
#define TEST_ARRAY_SIZE 100000
#define RAND_LIMIT 1000000

typedef enum SortingErrorCode
{
    ok,
    memoryError
} SortingErrorCode;

// errorCode всегда ок, чтобы была одинаковая сигнатура с countingSort
static SortingErrorCode bubbleSort(int *const array, const size_t size)
{
    if (size == 0)
    {
        return ok;
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
    return ok;
}

static void printArray(int const *const array, const size_t size)
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
    int minElement = array[0];
    for (size_t i = 0; i < size; ++i)
    {
        if (maxElement < array[i])
        {
            maxElement = array[i];
        }
        if (minElement > array[i])
        {
            minElement = array[i];
        }
    }
    const int countingArraySize = maxElement - minElement + 1;
    int *countArray = (int *)calloc(countingArraySize, sizeof(int));
    if (countArray == NULL)
    {
        return memoryError;
    }
    for (size_t i = 0; i < size; ++i)
    {
        ++countArray[array[i] - minElement];
    }
    size_t currentIndex = 0;
    for (int i = 0; i < countingArraySize; ++i)
    {
        for (size_t j = currentIndex; j < countArray[i] + currentIndex; ++j)
        {
            array[j] = i + minElement;
        }
        currentIndex += countArray[i];
    }
    free(countArray);
    return ok;
}

static float compareTime(bool *const memoryError)
{
    int *array1 = (int *)malloc(TEST_ARRAY_SIZE * sizeof(int));
    if (array1 == NULL)
    {
        *memoryError = true;
        return 0;
    }

    int *array2 = (int *)malloc(TEST_ARRAY_SIZE * sizeof(int));
    if (array2 == NULL)
    {
        *memoryError = true;
        free(array1);
        return 0;
    }

    srand(time(NULL));
    for (size_t i = 0; i < TEST_ARRAY_SIZE; ++i)
    {
        int randomNumber = rand() % RAND_LIMIT;
        array1[i] = randomNumber;
        array2[i] = randomNumber;
    }

    time_t startTime1 = time(NULL);
    bubbleSort(array1, TEST_ARRAY_SIZE);
    time_t finishTime1 = time(NULL);
    double time1 = difftime(finishTime1, startTime1);
    free(array1);

    time_t startTime2 = time(NULL);
    SortingErrorCode ec = countingSort(array2, TEST_ARRAY_SIZE);
    time_t finishTime2 = time(NULL);
    double time2 = difftime(finishTime2, startTime2);
    free(array2);
    if (ec != ok)
    {
        *memoryError = true;
        return 0;
    }
    *memoryError = false;

    return time1 - time2;
}

static bool checkIfArrayIsSorted(int const *const array, size_t size)
{
    if (size == 1)
    {
        return true;
    }
    int previousElement = array[0];
    for (size_t i = 1; i < size; ++i)
    {
        if (previousElement > array[i])
        {
            return false;
        }
        previousElement = array[i];
    }
    return true;
}

static const bool testCase(int *const testArray,
                           SortingErrorCode (*sortingFunction)(int *const, const size_t), const size_t testArraySize)
{
    int *tempArray = (int *)malloc(testArraySize);
    if (tempArray == NULL)
    {
        return false;
    }

    memcpy(tempArray, testArray, testArraySize * sizeof(int));

    if (sortingFunction(tempArray, testArraySize) != ok)
    {
        free(tempArray);
        return false;
    }

    const bool answer = checkIfArrayIsSorted(tempArray, testArraySize);
    free(tempArray);
    return answer;
}

static bool test(void)
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
        if (!(testCase(tests[i], &bubbleSort, testArraySize) && testCase(tests[i], &countingSort, testArraySize)))
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return PROGRAM_FAILED_TESTS;
    }

    bool memoryError = false;
    float timeDif = compareTime(&memoryError);
    if (memoryError)
    {
        printf("Недостаточно памяти\n");
        return MEMORY_ERROR;
    }

    if (timeDif < 0)
    {
        printf("Counting sort was %f seconds slower\n", timeDif * -1);
    }
    else if (timeDif > 0)
    {
        printf("Bubble sort was %f seconds slower\n", timeDif);
    }
    else
    {
        printf("Time of work of counting sort and bubble sort was equal\n");
    }

    return PROGRAM_FINISHED_CORRECTLY;
}
