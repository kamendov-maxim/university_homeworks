#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define INPUT_ERROR 3
#define ELEMENT_NOT_FOUND -1

const bool test(void);

static void printArray(int *array, size_t size)
{
   for (size_t i = 0; i < size; ++i)
   {
      printf("%d ", array[i]);
   }
   printf("\n");
}

static void swap(int *firstValue, int *secondValue)
{
   int buffer = *firstValue;
   *firstValue = *secondValue;
   *secondValue = buffer;
}

static size_t partition(int *array, size_t leftElement, size_t rightElement)
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

static void insertSort(int array[], int leftElement, int rightElement)
{
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
}

static void smartQuickSort(int array[], int leftElement, int rightElement)
{
   if (rightElement - leftElement + 1 < 10)
   {
      insertSort(array, leftElement, rightElement + 1);
      return;
   }
   if (leftElement < rightElement)
   {
      int currentSeparator = partition(array, 0, rightElement);
      smartQuickSort(array, leftElement, currentSeparator - 1);
      smartQuickSort(array, currentSeparator + 1, rightElement);
   }
}

static void generateRandomArray(int * array, size_t size)
{
   for (size_t i = 0; i < size; ++i)
   {
      srand(time(NULL));
      array[i] = rand() % 100;
   }
}

static const bool testSwapFunction(void)
{
   int firstValue = 0;
   int secondValue = 1;
   swap(&firstValue, &secondValue);
   return firstValue == 1 && secondValue == 0;
}

static const bool testStarterForArrays(int testArray[], int answerArray[], int size)
{
   for (size_t i = 0; i < size; ++i)
   {
      if (testArray[i] != answerArray[i])
      {
         return false;
      }
   }
   return true;
}

static const bool testPartitionFunction(void)
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

   return testStarterForArrays(testArray1, answerArray1, 9) && testStarterForArrays(testArray2, answerArray2, 6) && testStarterForArrays(testArray3, answerArray3, 5) && testStarterForArrays(testArray4, answerArray4, 1);
}

static const bool testSmartQuickSort(void)
{
   int testArray1[5] = {5, 4, 3, 2, 1};
   int answerArray1[5] = {1, 2, 3, 4, 5};

   int testArray2[5] = {1, 2, 3, 4, 5};
   int answerArray2[5] = {1, 2, 3, 4, 5};

   int testArray3[1] = {1};
   int answerArray3[1] = {1};

   smartQuickSort(testArray1, 0, 5 - 1);

   smartQuickSort(testArray2, 0, 5 - 1);

   smartQuickSort(testArray3, 0, 1 - 1);

   return testStarterForArrays(testArray1, answerArray1, 5) && testStarterForArrays(testArray2, answerArray2, 5) && testStarterForArrays(testArray3, answerArray3, 1);
}

const bool test(void)
{
   return testSwapFunction() && testPartitionFunction() && testSmartQuickSort();
}

int main(void)
{
   if (!test())
   {
      return PROGRAM_FAILED_TESTS;
   }

   int size = 0;
   while (size <= 0)
   {
      printf("Enter the size of your array: ");
      if (scanf("%d", &size) != 1)
      {
         return INPUT_ERROR;
      }
      if (size <= 0)
      {
         printf("\nSize of your array should be at least 1\n");
      }
   }

   int *array = (int *)malloc(size * sizeof(int));
   if (array == NULL)
   {
      printf("\nSorry but something went wrong\n");
      return MEMORY_ERROR;
   }

   printf("Enter numbers of your array one by one each other on the next line: \n");

   for (size_t i = 0; i < size; ++i)
   {
      printf("Enter %lu number of your array: ", i + 1);
      int currentNumber = 0;
      scanf("%d", &currentNumber);
      array[i] = currentNumber;
   }

   printf("\nYour array before getting sorted: \n");
   printArray(array, size);

   smartQuickSort(array, 0, size - 1);

   printf("\nYour array after getting sorted: \n");
   printArray(array, size);

   return PROGRAM_FINISHED_CORRECTLY;
}
