#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void generateRandomArray(int array[], int size);
void printArray(int array[], int size);

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

    int *k_array = malloc(k * sizeof(int));
    if (k_array == NULL)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    generateRandomArray(k_array, k);

    

    printArray(array, size);
    printArray(k_array, k);


    for (int i = 0; i < k; ++i)
    {
        
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

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int binarySearch(int array[], int x, int leftEdge, int rightEdge, int *answer)
{
    while (leftEdge <= rightEdge)
    {
        int middleElement = leftEdge + (rightEdge - leftEdge) / 2;

        if (array[middleElement] == x)
        {
            *answer = middleElement;
            return 0;
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
