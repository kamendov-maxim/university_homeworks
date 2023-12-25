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

static void insertSort(int *const array, size_t leftElement, size_t rightElement)
{
   for (size_t i = leftElement + 1; i < rightElement; ++i)
   {
      int currentElement = array[i];
      int j = i - 1;
      bool arrayWasChanged = false;
      while (j >= leftElement && array[j] >= currentElement)
      {
         array[j + 1] = array[j];
         arrayWasChanged = true;
         if (j == 0)
         {
            break;
         }
         --j;
      }
      if (arrayWasChanged)
      {
         array[j] = currentElement;
      }
   }
}

static void smartQuickSort(int *const array, size_t leftElement, size_t rightElement)
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

static void generateRandomArray(int *const array, size_t const size)
{
   srand((time(NULL)));
   for (int i = 0; i < size; ++i)
   {
      array[i] = rand() % RANDINT_DIGITS_LIMIT;
   }
}

static int binarySearch(int const *const array, int const elementWeAreLookingFor, size_t rightEdge)
{
   size_t leftEdge = 0;
   while (leftEdge <= rightEdge)
   {
      size_t middleElement = leftEdge + (rightEdge - leftEdge) / 2;
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

   return ELEMENT_NOT_FOUND;
}

static const bool binarySearchTestCase(int const *const testArray, const int elementWeAreLookingFor, const long answer, const size_t testSize)
{
   return binarySearch(testArray, elementWeAreLookingFor, testSize) == answer;
}

static const bool testBinarySearch(void)
{
   const size_t testSize1 = 10;
   const int testArray1[testSize1] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   const int testElementWeAreLookingFor1 = 3;
   const long answer1 = 3;

   const size_t testSize2 = 6;
   const int testArray2[testSize2] = {0, 2, 4, 5, 7, 10};
   const int testElementWeAreLookingFor2 = 0;
   const long answer2 = 0;

   const size_t testSize3 = 4;
   const int testArray3[testSize3] = {5, 6, 8, 42};
   const int testElementWeAreLookingFor3 = 10;
   const long answer3 = -1;

   return binarySearchTestCase(testArray1, testElementWeAreLookingFor1, answer1, testSize1)
   && binarySearchTestCase(testArray2, testElementWeAreLookingFor2, answer2, testSize2)
   && binarySearchTestCase(testArray3, testElementWeAreLookingFor3, answer3, testSize3);
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

static const bool testSmartQuickSort(void)
{
   const size_t testSize1 = 5;
   int testArray1[testSize1] = {5, 4, 3, 2, 1};
   int answerArray1[testSize1] = {1, 2, 3, 4, 5};

   const size_t testSize2 = 5;
   int testArray2[testSize2] = {1, 2, 3, 4, 5};
   int answerArray2[testSize2] = {1, 2, 3, 4, 5};

   const size_t testSize3 = 1;
   int testArray3[testSize3] = {1};
   int answerArray3[testSize3] = {1};

   smartQuickSort(testArray1, 0, testSize1 - 1);
   smartQuickSort(testArray2, 0, testSize2 - 1);
   smartQuickSort(testArray3, 0, testSize3 - 1);

   return memcmp(testArray1, answerArray1, testSize1) == 0
   && memcmp(testArray2, answerArray2, testSize2) == 0
   && memcmp(testArray3, answerArray3, testSize3) == 0;
}

static const bool test(void)
{

   return testSwapFunction()
   && testPartitionFunction()
   && testSmartQuickSort()
   && testBinarySearch();
}

int main(void)
{
   if (!test())
   {
      printf("Sorry but the program doesnt work\n");
      return PROGRAM_FAILED_TESTS;
   }

   size_t size = 0;
   while (size == 0)
   {
      printf("Enter the size of your array: ");
      if (scanf("%lu", &size) != 1)
      {
         return INPUT_ERROR;
      }
      if (size == 0)
      {
         printf("\nSize of your array should be at least 1\n");
      }
   }

   size_t k = 0;
   printf("Enter number of tests: ");
   if (scanf("%lu", &k) != 1)
   {
      return INPUT_ERROR;
   }

   int *array = (int *)malloc(size * sizeof(int));
   if (array == NULL)
   {
      printf("\nNot enough memory\n");
      return MEMORY_ERROR;
   }

   generateRandomArray(array, size);
   printf("Your random array: ");
   printArray(array, size);

   smartQuickSort(array, 0, size - 1);

   for (size_t i = 0; i < k; ++i)
   {
      int randomNumber = rand() % RANDINT_DIGITS_LIMIT;

      printf("test #%lu", i+1);
      printf(" number: % d", randomNumber);
      printf(", answer: ");
      char * answer = (binarySearch(array, randomNumber, size) == -1 ? "there is no such number in the array\n": "this number was found in the array\n");
      printf("%s", answer);
   }
   free(array);

   return PROGRAM_FINISHED_CORRECTLY;
}
