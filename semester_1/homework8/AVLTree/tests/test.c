#include <stdbool.h>
#include <string.h>

#include "test.h"
#include "../AVLTree/AVLTree.h"
#include "../userInput.h"

#include <stdio.h>

static bool testCase(size_t testLen, UserInput const *const testCommands, char ** keys
        , char **values, char const **charAnswers, bool const *const boolAnswers)
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

            dictionaryErrorCode = append(dictionary, keys[currentKey], values[currentValue], true);
            if (dictionaryErrorCode != ok)
            {
                deleteDictionary(dictionary);
                return false;
            }
            ++currentKey;
            ++currentValue;
            break;
        }

        case getValueCommand:
        {
            if (strcmp(getValue(dictionary, keys[currentKey]), charAnswers[currentAnswer]) != 0)
            {
                deleteDictionary(dictionary);
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
                deleteDictionary(dictionary);
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
                deleteDictionary(dictionary);
                return false;
            }
            ++currentKey;
            break;
        }

        default:
            break;
        }
    }
    deleteDictionary(dictionary);
    return true;
}

const bool test(void)
{
    UserInput testCommands1[5] = {appendCommand, appendCommand, deleteElementCommand, checkKeyCommand, getValueCommand};
    char *testKeys1[5] = {"five", "six", "six", "six", "five"};
    char *testValues1[2] = {"five", "six"};
    char const *charAnswers1[1] = {"five"};
    bool const boolAnswers1[] = {false};
    bool testCase1 = testCase(5, testCommands1, testKeys1, testValues1, charAnswers1, boolAnswers1);

    UserInput testCommands2[5] = {checkKeyCommand, appendCommand, checkKeyCommand, deleteElementCommand, checkKeyCommand};
    char *testKeys2[5] = {"one", "one", "one", "one", "one"};
    char *testValues2[1] = {"one"};
    char const *charAnswers2[0] = {};
    bool const boolAnswers2[3] = {false, true, false};
    bool testCase2 = testCase(5, testCommands2, testKeys2, testValues2, charAnswers2, boolAnswers2);

    UserInput testCommands3[7] = {appendCommand, getValueCommand, appendCommand, getValueCommand, deleteElementCommand, appendCommand, getValueCommand};
    char *testKeys3[7] = {"one", "one", "one", "one", "one", "one", "one"};
    char *testValues3[3] = {"one", "two", "one"};
    char const *charAnswers3[3] = {"one", "two", "one"};
    bool const boolAnswers3[0] = {};
    bool testCase3 = testCase(4, testCommands3, testKeys3, testValues3, charAnswers3, boolAnswers3);

    return testCase1 && testCase2 && testCase3;
}
