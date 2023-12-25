#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define INPUT_ERROR 3
#define ELEMENT_NOT_FOUND -1
#define RANDINT_DIGITS_LIMIT 100

static void printArray(int const *const array, size_t const size)
{
   for (size_t i = 0; i < size; ++i)
   {
      printf("%d ", array[i]);
   }
   printf("\n");
}

static void swap(int *const firstValue, int *const secondValue)
{
   int buffer = *firstValue;
   *firstValue = *secondValue;
   *secondValue = buffer;
}

static size_t partition(int *const array, size_t leftElement, size_t rightElement)
{
   rightElement -= 1;
   int currentSeparator = array[leftElement];
   size_t i = rightElement;

   for (size_t j = rightElement; j > leftElement; --j)
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

static void generateRandomArray(int *const array, size_t const size)
{
   srand((time(NULL)));
   for (int i = 0; i < size; ++i)
   {
      array[i] = rand() % RANDINT_DIGITS_LIMIT;
   }
}

static const bool testSwapFunction(void)
{
   int firstValue = 0;
   int secondValue = 1;
   swap(&firstValue, &secondValue);
   return firstValue == 1 && secondValue == 0;
}

static const bool testPartitionFunction(void)
{
   const size_t testSize1 = 9;
   int testArray1[testSize1] = {61, 99, 60, 80, 27, 57, 35, 81, 80};
   int const answerArray1[testSize1] = {27, 57, 60, 35, 61, 99, 80, 81, 80};

   const size_t testSize2 = 6;
   int testArray2[testSize2] = {43, 36, 55, 60, 94, 24};
   int const answerArray2[testSize2] = {24, 36, 43, 55, 60, 94};

   const size_t testSize3 = 5;
   int testArray3[testSize3] = {87, 91, 53, 37, 42};
   int const answerArray3[testSize3] = {37, 42, 53, 87, 91};

   const size_t testSize4 = 1;
   int testArray4[testSize4] = {5};
   int const answerArray4[testSize4] = {5};

   partition(testArray1, 0, testSize1);
   partition(testArray2, 0, testSize2);
   partition(testArray3, 0, testSize3);
   partition(testArray4, 0, testSize4);

   return memcmp(testArray1, answerArray1, testSize1) == 0
   && memcmp(testArray2, answerArray2, testSize2) == 0
   && memcmp(testArray3, answerArray3, testSize3) == 0
   && memcmp(testArray4, answerArray4, testSize4) == 0;
}

static const bool test(void)
{

   return testSwapFunction()
   && testPartitionFunction();
}

int main()
{
    if (!test())
    {
        printf("\nSorry but the program does not work correctly\n");
        return PROGRAM_FAILED_TESTS;
    }

    printf("\nEnter the size of your array: ");
    size_t size = 0;
    if (scanf("%zd", &size) != 1)
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    while (size <= 0)
    {
        printf("\nSize of your array should be at least 1\n");
        printf("Enter the size of your array: ");
        scanf("%zd", &size);
    }

    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL)
    {
        printf("\nNot enough memory\n");
        return MEMORY_ERROR;
    }

    generateRandomArray(array, size);

    printf("\nYour random array before parting:\n");
    printArray(array, size);
    partition(array, 0, size);
    printf("\nAfter:\n");
    printArray(array, size);

    free(array);
}
