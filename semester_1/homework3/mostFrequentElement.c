#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int partition(int array[], int leftElement, int rightElement);
void swap(int *firstValue, int *secondValue);
int insertSort(int array[], int leftElement, int rightElement);
int smartQuickSort(int array[], int leftElement, int rightElement);
int mostFrequentElement(int array[], int size);

bool test(void);
bool testSmartQuickSort(void);
bool testPartitionFunction(void);
bool testSwapFunction(void);
bool testStarterForPartitionFunction(int testArray[], int answerArray[], int size);
bool testStarterForMostFrequentELement(int testArray[], int size, int answer);
bool testMostFrequentElementFunction(void);

int main()
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return 1;
    }

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

    printf("Enter numbers of your array one by one each other on the next line: \n");

    for (int i = 0; i < size; ++i)
    {
        printf("Enter %d number of your array: ", i + 1);
        int currentNumber = 0;
        scanf("%d", &currentNumber);
        array[i] = currentNumber;
    }

    int errorCode = smartQuickSort(array, 0, size - 1);
    if (errorCode != 0)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    printf("\nThe most frequent element in the array is %d\n", mostFrequentElement(array, size));

    return 0;
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

int smartQuickSort(int array[], int leftElement, int rightElement)
{
    if (rightElement < leftElement)
    {
        return 2;
    }

    if (rightElement - leftElement + 1 < 10)
    {
        int errorCode = insertSort(array, leftElement, rightElement + 1);
        if (errorCode != 0)
        {
            return 1;
        }
        return 0;
    }
    if (leftElement < rightElement)
    {
        int currentSeparator = partition(array, 0, rightElement);
        smartQuickSort(array, leftElement, currentSeparator - 1);
        smartQuickSort(array, currentSeparator + 1, rightElement);
    }
    return 0;
}

int insertSort(int array[], int leftElement, int rightElement)
{
    if (rightElement < leftElement)
    {
        return 1;
    }

    for (int i = leftElement; i < rightElement; ++i)
    {
        int currentElement = array[i];
        int j = i - 1;
        while (j >= leftElement && array[j] >= currentElement)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = currentElement;
    }
    return 0;
}

int partition(int array[], int leftElement, int rightElement)
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

    return i;
}

void swap(int *firstValue, int *secondValue)
{
    int buffer = *firstValue;
    *firstValue = *secondValue;
    *secondValue = buffer;
}

bool test(void)
{
    if (!(testSwapFunction() * testPartitionFunction() * testSmartQuickSort() * testMostFrequentElementFunction()))
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

bool testStarterForArrays(int testArray[], int answerArray[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (testArray[i] != answerArray[i])
        {
            return false;
        }
    }
    return true;
}

bool testPartitionFunction(void)
{
    int testArray1[9] = {61, 99, 60, 80, 27, 57, 35, 81, 80};
    int answerArray1[9] = {27, 57, 60, 35, 61, 99, 80, 81, 80};

    int testArray2[6] = {43, 36, 55, 60, 94, 24};
    int answerArray2[6] = {24, 36, 43, 55, 60, 94};

    int testArray3[5] = {87, 91, 53, 37, 42};
    int answerArray3[5] = {37, 42, 53, 87, 91};

    int testArray4[1] = {5};
    int answerArray4[1] = {5};

    partition(testArray1, 0, 9);
    partition(testArray2, 0, 6);
    partition(testArray3, 0, 5);
    partition(testArray4, 0, 1);

    if (!(testStarterForArrays(testArray1, answerArray1, 9) * testStarterForArrays(testArray2, answerArray2, 6) * testStarterForArrays(testArray3, answerArray3, 5) * testStarterForArrays(testArray4, answerArray4, 1)))
    {
        return false;
    }

    return true;
}

bool testSmartQuickSort(void)
{

    int testArray1[5] = {5, 4, 3, 2, 1};
    int answerArray1[5] = {1, 2, 3, 4, 5};

    int testArray2[5] = {1, 2, 3, 4, 5};
    int answerArray2[5] = {1, 2, 3, 4, 5};

    int testArray3[1] = {1};
    int answerArray3[1] = {1};

    int errorCode = smartQuickSort(testArray1, 0, 5 - 1);
    if (errorCode != 0)
    {
        return false;
    }

    errorCode = smartQuickSort(testArray2, 0, 5 - 1);
    if (errorCode != 0)
    {
        return false;
    }

    errorCode = smartQuickSort(testArray3, 0, 1 - 1);
    if (errorCode != 0)
    {
        return false;
    }

    if (!(testStarterForArrays(testArray1, answerArray1, 5) * testStarterForArrays(testArray2, answerArray2, 5) * testStarterForArrays(testArray3, answerArray3, 1)))
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