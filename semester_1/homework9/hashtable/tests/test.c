#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test.h"

#define LOADTEST_MAX_TIME 3
#define LOADTEST_STRING_LENGTH 10
#define LOADTEST_STRING_NUMBER 100000
#define LOADTEST_MAX_KEY_LENGTH 6
#define LOADTEST_BUCKET_NUMBER 1000

typedef enum command
{
    addCommand,
    deleteCommand,
    getFrequencyCommand
} command;

static char *generateString(size_t length)
{
    char *string = (char *)malloc(length * sizeof(char));
    if (string == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < length - 1; ++i)
    {
        string[i] = 'a' + rand() % 26;
    }
    string[length - 1] = '\0';
    return string;
}

static const size_t getNumberLength(size_t number)
{
    size_t count = 0;
    do
    {
        number = number / 10;
        ++count;
    } while (number != 0);

    return count;
}

static const bool loadTest(void)
{
    size_t frequency = 0;
    size_t al = 0;
    size_t ml = 0;
    size_t coef = 0;
    HashTableErrorCode hashTableErrorCode = okHashTable;
    double start = clock() / CLOCKS_PER_SEC;
    srand(time(NULL));

    HashTable *hashTable = createHashTable(LOADTEST_BUCKET_NUMBER);
    if (hashTable == NULL)
    {
        return false;
    }
    for (size_t i = 0; i < LOADTEST_STRING_NUMBER; ++i)
    {
        char *randomValue = generateString(LOADTEST_STRING_LENGTH);
        if (randomValue == NULL)
        {
            deleteHashTable(hashTable);
            return false;
        }

        HashTableErrorCode errorCode = addValue(hashTable, randomValue, false);
        if (errorCode != okHashTable)
        {
            free(randomValue);
            deleteHashTable(hashTable);
            return false;
        }

        frequency = getFrequency(hashTable, randomValue);
        getStatistics(hashTable, &al, &ml, &coef);
    }

    deleteHashTable(hashTable);
    double finish = clock() / CLOCKS_PER_SEC;

    return finish - start <= LOADTEST_MAX_TIME;
}

static const bool testCase(command const *const commandsArray, size_t const commandAmount, char const *const *const values, size_t const *const sizetAnswers)
{
    size_t const buckets = 100;
    HashTable *hashTable = createHashTable(buckets);
    if (hashTable == NULL)
    {
        return false;
    }

    size_t currentValue = 0;
    size_t currentSztAnswer = 0;
    HashTableErrorCode hashTableErrorCode = okHashTable;
    for (size_t i = 0; i < commandAmount; ++i)
    {
        command currentCommand = commandsArray[i];
        switch (currentCommand)
        {
        case addCommand:
        {
            hashTableErrorCode = addValue(hashTable, values[currentValue], true);
            if (hashTableErrorCode != okHashTable)
            {
                deleteHashTable(hashTable);
                return false;
            }
            ++currentValue;

            break;
        }

        case deleteCommand:
        {
            deleteElementFromTable(hashTable, values[currentValue]);
            ++currentValue;
            break;
        }

        case getFrequencyCommand:
        {
            if (getFrequency(hashTable, values[currentValue]) != sizetAnswers[currentSztAnswer])
            {
                deleteHashTable(hashTable);
                return false;
            }
            ++currentValue;
            ++currentSztAnswer;

            break;
        }

        default:
            break;
        }
    }
    deleteHashTable(hashTable);
    return true;
}

static const bool checkStatisticsChange(HashTable *const hashtable, char const *const value, const command cmd, size_t ml, size_t al, float k)
{
    switch (cmd)
    {
    case addCommand:
    {
        HashTableErrorCode hashTableErrorCode = addValue(hashtable, value, true);
        if (hashTableErrorCode != okHashTable)
        {
            return false;
        }
        break;
    }

    case deleteCommand:
    {
        deleteElementFromTable(hashtable, value);
        break;
    }

    default:
    {
        false;
        break;
    }
    }

    size_t averageLength = 0;
    size_t maxLength = 0;
    float coef = 0;
    getStatistics(hashtable, &averageLength, &maxLength, &coef);
    if (averageLength != al || maxLength != ml || coef != k)
    {
        return false;
    }

    return true;
}

static const bool testStatisticsFunction(void)
{
    size_t const buckets = 10;
    HashTable *hashTable = createHashTable(buckets);
    if (hashTable == NULL)
    {
        return NULL;
    }
    const size_t statisticsTestsAmount = 4;
    command commands[statisticsTestsAmount] = {addCommand, addCommand, addCommand, addCommand};
    const char *const values[statisticsTestsAmount] = {"a", "a", "b", "c"};
    const int ml[statisticsTestsAmount] = {1, 2, 2, 2};
    const int al[statisticsTestsAmount] = {0, 0, 0, 0};
    const float k[statisticsTestsAmount] = {0.1, 0.1, 0.2, 0.3};
    for (size_t i = 0; i < statisticsTestsAmount; ++i)
    {
        if (!checkStatisticsChange(hashTable, values[i], commands[i], ml[i], al[i], k[i]))
        {
            deleteHashTable(hashTable);
            return false;
        }
    }
    deleteHashTable(hashTable);
    return true;
}

const bool test(void)
{
    command commandsArray1[7] = {addCommand, addCommand, addCommand, getFrequencyCommand, getFrequencyCommand,
                                 deleteCommand, getFrequencyCommand};
    const char *const values1[7] = {"a", "b", "a", "b", "a", "a", "a"};
    const size_t sizetAnswers1[3] = {1, 2, 1};
    const bool testCase1 = testCase(commandsArray1, 7, values1, sizetAnswers1);

    command commandsArray2[6] = {addCommand, getFrequencyCommand, deleteCommand, getFrequencyCommand, addCommand,
                                 getFrequencyCommand};
    const char *const values2[6] = {"a", "a", "a", "a", "a", "a"};
    const size_t sizetAnswers2[3] = {1, 0, 1};
    const bool testCase2 = testCase(commandsArray2, 6, values2, sizetAnswers2);

    return testCase1 && testCase2 && loadTest();
}
