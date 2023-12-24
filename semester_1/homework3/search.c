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
bool testStarterForPartitionFunction(int testArray[], int answerArray[], int size);
bool testBinarySearch(void);
bool testSortings(void);
bool checkIfArrayIsSorted(int array[], int size);
bool testStarterForArrays(int testArray[], int answerArray[], int size);

int main()
{
   if (!test())
   {
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

   printf("\nYour array before getting sorted: \n");
   printArray(array, size);

   int errorCode = smartQuickSort(array, 0, size - 1);
   if (errorCode == 1)
   {
      printf("\nSorry but something went wrong\n");
      return 1;
   }

   if (errorCode == 2)
   {
      printf("\nsmartQuickSort: Incorrect input\n");
      return 1;
   }

   printf("\nYour array after getting sorted: \n");
   printArray(array, size);

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
   if (!(testSwapFunction() * testPartitionFunction() * testSmartQuickSort() * testBinarySearch()))
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

    if (!(testStarterForBinarySearch(testArray1, testElementWeAreLookingFor1, answer1, 10) || !testStarterForBinarySearch(testArray2, testElementWeAreLookingFor2, answer2, 6) || !testStarterForBinarySearch(testArray3, testElementWeAreLookingFor2, answer3, 4)))
    {
        return false;
    }

    return true;
}