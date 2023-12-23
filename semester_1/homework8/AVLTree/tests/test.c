#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "test.h"
#include "../AVLTree/AVLTree.h"
#include "../userInput.h"

#define LOADTEST_STRING_NUMBER 100000
#define MAX_KEY_LENGTH 6
#define LOADTEST_STRING_LENGTH 10
#define LOADTEST_MAX_TIME 5

#include <stdio.h>

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
    Dictionary *dictionary = createDictionary();
    if (dictionary == NULL)
    {
        return false;
    }
    DictionaryErrorCode dictionaryErrorCode = ok;
    double start = clock() / CLOCKS_PER_SEC;
    srand(time(NULL));

    for (size_t i = 0; i < LOADTEST_STRING_NUMBER; ++i)
    {
        char *randomValue = generateString(LOADTEST_STRING_LENGTH);
        if (randomValue == NULL)
        {
            deleteDictionary(&dictionary);
            return false;
        }

        char *key = malloc(getNumberLength(i) * sizeof(char));
        if (key == NULL)
        {
            free(randomValue);
            deleteDictionary(&dictionary);
            return false;
        }

        sprintf(key, "%zu", i);

        if (addElement(dictionary, key, randomValue, false) != ok)
        {
            free(randomValue);
            free(key);
            deleteDictionary(&dictionary);
            return false;
        }
    }

    double finish = clock() / CLOCKS_PER_SEC;

    for (size_t i = 0; i < LOADTEST_STRING_NUMBER; ++i)
    {
        char *key = malloc((MAX_KEY_LENGTH + 1) * sizeof(char));
        if (keyCheck(dictionary, key))
        {
            deleteDictionary(&dictionary);
            return false;
        }
    }

    return finish - start <= LOADTEST_MAX_TIME;
}

static const bool testCase(size_t testLen, UserInput const *const testCommands,
                           char **keys, char **values, char const **charAnswers, bool const *const boolAnswers)
{
    Dictionary *dictionary = createDictionary();
    if (dictionary == NULL)
    {
        return false;
    }
    size_t currentKey = 0;
    size_t currentValue = 0;
    size_t currentAnswer = 0;
    size_t currentBool = 0;

    DictionaryErrorCode dictionaryErrorCode = ok;
    for (size_t currentTest = 0; currentTest < testLen; ++currentTest)
    {
        switch (testCommands[currentTest])
        {
        case appendCommand:
        {

            dictionaryErrorCode = addElement(dictionary, keys[currentKey], values[currentValue], true);
            if (dictionaryErrorCode != ok)
            {
                deleteDictionary(&dictionary);
                return false;
            }
            ++currentKey;
            ++currentValue;
            break;
        }

        case getValueCommand:
        {
            const char *const value = getValue(dictionary, keys[currentKey]);
            if (value == NULL)
            {
                return false;
            }

            if (strcmp(value, charAnswers[currentAnswer]) != 0)
            {
                deleteDictionary(&dictionary);
                return false;
            }
            ++currentKey;
            ++currentAnswer;
            break;
        }

        case checkKeyCommand:
        {
            if (keyCheck(dictionary, keys[currentKey]) != boolAnswers[currentBool])
            {
                deleteDictionary(&dictionary);
                return false;
            }
            ++currentKey;
            ++currentBool;
            break;
        }

        case deleteElementCommand:
        {
            deleteElement(dictionary, keys[currentKey]);
            if (keyCheck(dictionary, keys[currentKey]))
            {
                deleteDictionary(&dictionary);
                return false;
            }
            ++currentKey;
            break;
        }

        default:
            break;
        }
    }
    deleteDictionary(&dictionary);
    return true;
}

const bool test(void)
{
    UserInput testCommands1[5] = {appendCommand, appendCommand, deleteElementCommand,
                                  checkKeyCommand, getValueCommand};
    char *testKeys1[5] = {"five", "six", "six", "six", "five"};
    char *testValues1[2] = {"five", "six"};
    char const *charAnswers1[1] = {"five"};
    bool const boolAnswers1[] = {false};
    bool testCase1 = testCase(5, testCommands1, testKeys1, testValues1, charAnswers1, boolAnswers1);

    UserInput testCommands2[5] = {checkKeyCommand, appendCommand, checkKeyCommand,
                                  deleteElementCommand, checkKeyCommand};
    char *testKeys2[5] = {"one", "one", "one", "one", "one"};
    char *testValues2[1] = {"one"};
    char const *charAnswers2[0] = {};
    bool const boolAnswers2[3] = {false, true, false};
    bool testCase2 = testCase(5, testCommands2, testKeys2, testValues2, charAnswers2, boolAnswers2);

    UserInput testCommands3[7] = {appendCommand, getValueCommand, appendCommand,
                                  getValueCommand, deleteElementCommand, appendCommand, getValueCommand};
    char *testKeys3[7] = {"one", "one", "one", "one", "one", "one", "one"};
    char *testValues3[3] = {"one", "two", "one"};
    char const *charAnswers3[3] = {"one", "two", "one"};
    bool const boolAnswers3[0] = {};
    bool testCase3 = testCase(4, testCommands3, testKeys3, testValues3, charAnswers3, boolAnswers3);

    UserInput testCommands4[7] = {appendCommand, appendCommand, appendCommand, appendCommand,
                                  appendCommand, appendCommand, appendCommand};
    char *testKeys4[7] = {"1", "2", "3", "4", "5", "6", "7"};
    char *testValues4[7] = {"1", "2", "3", "4", "5", "6", "7"};
    char const *charAnswers4[0] = {};
    bool const boolAnswers4[0] = {};
    bool testCase4 = testCase(4, testCommands4, testKeys4, testValues4, charAnswers4, boolAnswers4);

    return testCase1 && testCase2 && testCase3 && testCase4 && loadTest();
}
