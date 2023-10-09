#include <stdio.h>
#include <stdbool.h>

#define SIZE sizeof(int) * 8

int decimalToBinary(int number, int answer[]);
void printBinary(int array[]);

int main(int argc, char const *argv[])
{
    int number = 4;
    int answer[SIZE] = {0};

    int errorCode = decimalToBinary(number, answer);

    printBinary(answer);

    
    return 0;
}

int decimalToBinary(int number, int answer[])
{
    int bit = 1;
    for (int i = SIZE - 1; i < SIZE; --i)
    {
        answer[i] = ((number & bit) ? 1: 0);
        number = number >> 1;
    }
    return 0;
}

void printBinary(int array[])
{
    for (int i = 0; i < SIZE; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}