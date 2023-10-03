#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int partition(int array[], int leftElement, int rightElement);
void swap(int *firstValue, int *secondValue);
void printArray(int array[], int size);
void generateRandomArray(int array[], int size);
int insertSort(int array[], int leftElement, int rightElement);
int binarySearch(int array[], int elementWeAreLookingFor, int leftEdge, int rightEdge);
int smartQuickSort(int array[], int leftElement, int rightElement);

bool test(void);
bool testSmartQuickSort(void);
bool testPartitionFunction(void);
bool testSwapFunction(void);
bool testStarterForBinarySearch(int testArray[], int elementWeAreLookingFor, int answer, int size);
bool testStarterForPartitionFunction(int testArray[], int answerArray[], int sizeOfTestArray);
bool testBinarySearch(void);
bool testSortings(void);
bool checkIfArrayIsSorted(int array[], int size);

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

    generateRandomArray(array, size);

    printf("\nEnter the quantity of numbers for tests: ");
    int k = 0;
    scanf("%d", &k);
    printf("\n");

    int *k_array = malloc(k * sizeof(int));
    if (k_array == NULL)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    generateRandomArray(k_array, k);

    printf("Your array: ");
    printArray(array, size);
    printf("Your numbers to search in array: ");
    printArray(k_array, k);
    printf("\n");

    int errorCode = smartQuickSort(array, 0, size - 1);
    if (errorCode == 1)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    for (int i = 0; i < k; ++i)
    {
        int number = k_array[i];
        if (binarySearch(array, number, 0, size - 1) != -1)
        {
            printf("%d is in array\n", k_array[i]);
        }
        else
        {
            printf("%d is not in array\n", k_array[i]);
        }
    }
    printf("\n");

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

void swap(int *firstValue, int *secondValue)
{
    int buffer = *firstValue;
    *firstValue = *secondValue;
    *secondValue = buffer;
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

int smartQuickSort(int array[], int leftElement, int rightElement)
{
    if (rightElement < leftElement)
    {
        return 1;
    }

    if (rightElement - leftElement + 1 < 10)
    {
        insertSort(array, leftElement, rightElement + 1);
        return 0;
    }
    if (leftElement < rightElement)
    {
        int pivotIndex = partition(array, 0, rightElement);
        smartQuickSort(array, leftElement, pivotIndex - 1);
        smartQuickSort(array, pivotIndex + 1, rightElement);
    }
    return 0;
}

void generateRandomArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100;
    }
}

int insertSort(int array[], int leftElement, int rightElement)
{
    if (rightElement < leftElement)
    {
        return 1;
    }

    for (int i = leftElement; i < rightElement; i++)
    {
        int currentElement = array[i];
        int j = i - 1;
        while (j >= leftElement && array[j] >= currentElement)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = currentElement;
    }
    return 0;
}

int binarySearch(int array[], int elementWeAreLookingFor, int leftEdge, int rightEdge)
{
    while (leftEdge <= rightEdge)
    {
        int middleElement = leftEdge + (rightEdge - leftEdge) / 2;

        if (array[middleElement] == elementWeAreLookingFor)
        {
            return middleElement;
        }

        if (array[middleElement] < elementWeAreLookingFor)
        {
            leftEdge = middleElement + 1;
        }

        else
        {
            rightEdge = middleElement - 1;
        }
    }

    return -1;
}

bool test(void)
{
    if (!testSwapFunction() || !testBinarySearch() || !testPartitionFunction() || !testSortings())
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

bool testStarterForPartitionFunction(int testArray[], int answerArray[], int sizeOfTestArray)
{
    partition(testArray, 0, sizeOfTestArray - 1);
    for (int i = 0; i < 9; ++i)
    {
        if (testArray[i] != answerArray[i])
        {
            return false;
        }
    }
    return true;
}

bool testsForPartitionFunction(void)
{
    int testArray1[9] = {61, 99, 60, 80, 27, 57, 35, 81, 80};
    int answerArray1[9] = {27, 57, 60, 35, 61, 99, 80, 81, 80};

    int testArray2[6] = {43, 36, 55, 60, 94, 24};
    int answerArray2[6] = {24, 36, 43, 55, 60, 94};

    int testArray3[5] = {87, 91, 53, 37, 42};
    int answerArray3[5] = {37, 42, 53, 87, 91};

    int testArray4[1] = {5};
    int answerArray4[1] = {5};

    if (!testStarterForPartitionFunction(testArray1, answerArray1, 10) || !testStarterForPartitionFunction(testArray2, answerArray2, 10) || !testStarterForPartitionFunction(testArray3, answerArray3, 10) || !testStarterForPartitionFunction(testArray4, answerArray4, 10))
    {
        return false;
    }

    return true;
}

bool testStarterForBinarySearch(int testArray[], int elementWeAreLookingFor, int answer, int size)
{
    if (binarySearch(testArray, elementWeAreLookingFor, 0, size - 1) != answer)
    {
        return false;
    }

    return true;
}

bool testBinarySearch(void)
{
    int testArray1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int testElementWeAreLookingFor1 = 3;
    int answer1 = 4;

    int testArray2[6] = {5, 4, 7, 2, 0, 10};
    int testElementWeAreLookingFor2 = 0;
    int answer2 = 5;

    int testArray3[4] = {6, 42, 5, 8};
    int testElementWeAreLookingFor3 = 10;
    int answer3 = -1;

    if (!testStarterForBinarySearch(testArray1, testElementWeAreLookingFor1, answer1, 10) || !testStarterForBinarySearch(testArray2, testElementWeAreLookingFor2, answer2, 6) || !testStarterForBinarySearch(testArray3, testElementWeAreLookingFor2, answer3, 4))
    {
        return false;
    }

    return true;
}

bool testStarterForInsertSort(int testArray[], int size, int ec)
{
    int errorCode = insertSort(testArray, 0, size - 1);
    if (ec == 1)
    {
        if (errorCode != 1)
        {
            return false;
        }
        return true;
    }
    if (errorCode != 0 || !checkIfArrayIsSorted(testArray, 10))
    {
        return false;
    }
    return true;
}

bool testStarterForSmartQuickSort(int testArray[], int size, int ec)
{
    int errorCode = smartQuickSort(testArray, 0, size - 1);
    if (ec == 1)
    {
        if (errorCode != 1)
        {
            return false;
        }
        return true;
    }
    if (errorCode != 0 || !checkIfArrayIsSorted(testArray, 10))
    {
        return false;
    }
    return true;
}

bool testSortings(void)
{
    int testArray1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int errorCode1 = 0;

    int testArray2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int errorCode2 = 0;

    int testArray3[10] = {4, 8, 2, 3, 1, 9, 7, 5, 10, 6};
    int errorCode3 = 0;

    int testArray4[10] = {0};
    int errorCode4 = 0;

    int testArray5[1] = {1};
    int errorCode5 = 1;

    if (!testStarterForInsertSort(testArray1, 10, 0) 
    || !testStarterForInsertSort(testArray1, 10, 0) 
    || !testStarterForInsertSort(testArray2, 10, 0) 
    || !testStarterForInsertSort(testArray3, 10, 0) 
    || !testStarterForInsertSort(testArray4, 1, 1))
    {
        return false;
    }

    if (!testStarterForSmartQuickSort(testArray1, 10, 0) 
    || !testStarterForSmartQuickSort(testArray1, 10, 0) 
    || !testStarterForSmartQuickSort(testArray2, 10, 0) 
    || !testStarterForSmartQuickSort(testArray3, 10, 0) 
    || !testStarterForSmartQuickSort(testArray4, 1, 1))
    {
        return false;
    }
    
    return true;
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
