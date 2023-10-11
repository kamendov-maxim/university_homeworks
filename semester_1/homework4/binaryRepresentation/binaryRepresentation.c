#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define SIZE sizeof(int) * 8

int decimalToBinary(int number, int answer[]);
void printBinary(const int array[]);
int binaryAddition(int binary1[], int binary2[], int answer[]);

int binaryToDecimal(const int binNum[]);

bool test(void);
bool testDecimalToBinary(void);
bool testBinaryToDecimal(void);
bool testBinaryAdditionFunction(void);
bool testStarterDecimalToBinary(int test, const int answer[], int size);
bool testStarterAddition(int a, int b, int answer);

int main(int argc, char const *argv[])
{
    if (!test())
    {
        printf("Похоже, что сейчас программа не работает корректно");
        return 1;
    }

    setlocale(LC_ALL, "Ru.866");

    printf("Сейчас вам нужно будет ввести два числа\n");

    printf("Введите первое число: ");
    int number1 = 0;
    int elementsScanned1 = scanf("%d", &number1);
    if (elementsScanned1 != 1)
    {
        printf("Похоже, что-то пошло не так\n");
        return 1;
    }

    printf("Введите второе число: ");
    int number2 = 0;
    int elementsScanned2 = scanf("%d", &number2);
    if (elementsScanned2 != 1)
    {
        printf("Похоже, что-то пошло не так\n");
        return 1;
    }
    int exp = 2;
    for (int i = 0; i < SIZE; ++i)
    {
        exp = exp * 2;
    }

    int binary1[SIZE] = {0};
    int binary2[SIZE] = {0};

    int errorCode1 = decimalToBinary(number1, binary1);
    if (errorCode1 != 0)
    {
        printf("Похоже, что-то пошло не так\n");
        return 1;
    }

    int errorCode2 = decimalToBinary(number2, binary2);
    if (errorCode2 != 0)
    {
        printf("Похоже, что-то пошло не так\n");
    }

    printBinary(binary1);
    printBinary(binary2);

    int additionAnswer[SIZE] = {0};

    int errorCode3 = binaryAddition(binary1, binary2, additionAnswer);
    if (errorCode3 != 0)
    {
        printf("Похоже, что-то пошло не так\n");
        return 1;
    }

    printf("Сумма в двоичном представлении:\n");
    printBinary(additionAnswer);
    int ans = binaryToDecimal(additionAnswer);

    printf("%d", ans);

    return 0;
}

int decimalToBinary(int number, int answer[])
{
    int bit = 1;
    for (int i = SIZE - 1; i < SIZE; --i)
    {
        answer[i] = ((number & bit) ? 1 : 0);
        number = number >> 1;
    }
    return 0;
}

int binaryAddition(int binary1[], int binary2[], int answer[])
{
    int buffer = 0;
    for (int i = SIZE - 1; i < SIZE; --i)
    {
        int currentNumber = binary1[i] + binary2[i] + buffer;
        buffer = 0;
        if (currentNumber == 2)
        {
            buffer = 1;
            currentNumber = 0;
        }
        if (currentNumber == 3)
        {
            buffer = 1;
            currentNumber = 1;
        }
        answer[i] = currentNumber;
    }
    return 0;
}

void printBinary(const int array[])
{
    for (int i = 0; i < SIZE; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int binaryToDecimal(const int binNum[])
{
    int multiplier = 1;
    int result = 0;
    for (int i = SIZE - 1; i >= 0; --i)
    {
        result += binNum[i] * multiplier;
        multiplier *= 2;
    }
    return result;
}

bool test(void)
{
    if (!(testBinaryAdditionFunction() * testDecimalToBinary() * testBinaryToDecimal()))
    {
        return false;
    }
    return true;
}

bool testDecimalToBinary(void)
{
    int test1 = 5;
    int answer1[3] = {1, 0, 1};
    bool testAnswer1 = testStarterDecimalToBinary(test1, answer1, 3);

    int test2 = 10;
    int answer2[4] = {1, 0, 1, 0};
    bool testAnswer2 = testStarterDecimalToBinary(test2, answer2, 4);

    int test3 = 0;
    int answer3[1] = {0};
    bool testAnswer3 = testStarterDecimalToBinary(test3, answer3, 1);

    int test4 = -5;
    int answer4[3] = {0, 1, 1};
    bool testAnswer4 = testStarterDecimalToBinary(test4, answer4, 3);

    if (!(testAnswer1 * testAnswer2 * testAnswer3 * testAnswer4))
    {
        return false;
    }

    return true;
}

bool testStarterDecimalToBinary(int test, const int answer[], int size)
{
    int binary[SIZE] = {0};
    int errorCode = decimalToBinary(test, binary);
    if (errorCode != 0)
    {
        return false;
    }

    int j = size;
    for (int i = SIZE - 1; i >= SIZE - size; --i)
    {
        --j;
        if (answer[j] != binary[i])
        {
            printf("\n%d\n", j);
            return false;
        }
    }

    if (test >= 0)
    {
        for (int i = SIZE - 1 - size; i >= 0; --i)
        {
            if (binary[i] == 1)
            {
                return false;
            }
        }
    }

    if (test < 0)
    {
        for (int i = SIZE - 1 - size; i >= 0; --i)
        {
            if (binary[i] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

bool testBinaryToDecimal(void)
{
    int test1 = 5;
    int binary1[SIZE] = {0};
    int errorCode1 = decimalToBinary(test1, binary1);
    if (errorCode1 != 0)
    {
        return false;
    }

    int test2 = 2;
    int binary2[SIZE] = {0};
    int errorCode2 = decimalToBinary(test2, binary2);
    if (errorCode2 != 0)
    {
        return false;
    }

    int test3 = 0;
    int binary3[SIZE] = {0};
    int errorCode3 = decimalToBinary(test3, binary3);
    if (errorCode3 != 0)
    {
        return false;
    }

    int test4 = -5;
    int binary4[SIZE] = {0};
    int errorCode4 = decimalToBinary(test4, binary4);
    if (errorCode4 != 0)
    {
        return false;
    }

    if (!(test1 == binaryToDecimal(binary1)) * (test2 == binaryToDecimal(binary2)) * (test3 == binaryToDecimal(binary3)) * (test4 == binaryToDecimal(binary4)))
    {
        return false;
    }

    return true;
}

bool testBinaryAdditionFunction(void)
{
    int a1 = 5;
    int b1 = 10;
    int answer1 = 15;
    bool test1 = testStarterAddition(a1, b1, answer1);

    int a2 = 4;
    int b2 = -4;
    int answer2 = 0;
    bool test2 = testStarterAddition(a2, b2, answer2);

    int a3 = 6;
    int b3 = -2;
    int answer3 = 4;
    bool test3 = testStarterAddition(a3, b3, answer3);

    if (!(test1 * test2 * test3))
    {
        return false;
    }

    return true;
}

bool testStarterAddition(int a, int b, int answer)
{
    int binaryA[SIZE] = {0};
    int binaryB[SIZE] = {0};
    int errorCodeA = decimalToBinary(a, binaryA);
    if (errorCodeA != 0)
    {
        return false;
    }

    int errorCodeB = decimalToBinary(b, binaryB);
    if (errorCodeB != 0)
    {
        return false;
    }

    int binaryAnswer[SIZE] = {0};

    int errorCodeAddition = binaryAddition(binaryA, binaryB, binaryAnswer);
    if (errorCodeAddition != 0)
    {
        return false;
    }

    int decimalAnswer = binaryToDecimal(binaryAnswer);

    if (decimalAnswer != answer)
    {
        return false;
    }

    return true;
}