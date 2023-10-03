#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int partition(int array[], int leftElement, int rightElement);
void swap(int *firstValue, int *secondValue);
void printArray(int array[], int size);
void generateRandomArray(int array[], int size);
void insertionSort(int array[], int leftElement, int rightElement);
int binarySearch(int array[], int x, int leftEdge, int rightEdge);
void smartQuickSort(int array[], int leftElement, int rightElement);

bool test(void);
bool testSmartQuickSearch(void);
bool testPartitionFunction(void);
bool testSwapFunction(void);

int main()
{
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

    smartQuickSort(array, 0, size - 1);

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

void smartQuickSort(int array[], int leftElement, int rightElement)
{
    if (rightElement - leftElement + 1 < 10)
    {
        insertionSort(array, leftElement, rightElement + 1);
        return;
    }
    if (leftElement < rightElement)
    {
        int pivotIndex = partition(array, 0, rightElement);
        smartQuickSort(array, leftElement, pivotIndex - 1);
        smartQuickSort(array, pivotIndex + 1, rightElement);
    }
}

void generateRandomArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100;
    }
}

void insertionSort(int array[], int leftElement, int rightElement)
{
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
}

int binarySearch(int array[], int x, int leftEdge, int rightEdge)
{
    while (leftEdge <= rightEdge)
    {
        int middleElement = leftEdge + (rightEdge - leftEdge) / 2;

        if (array[middleElement] == x)
        {
            return middleElement;
        }

        if (array[middleElement] < x)
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
    
}



