#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "../String/String.h"
#include "../phoneBook/phoneBook.h"

#define OUTPUT_FILE_NAME "../tests/outputFile.txt"

static const bool compareFiles(char const *const filename1, char const *const filename2)
{
    FILE *file1 = fopen(filename1, "r");
    if (file1 == NULL)
    {
        return false;
    }

    FILE *file2 = fopen(filename2, "r");
    if (file2 == NULL)
    {
        fclose(file1);
        return false;
    }

    size_t len = 0;
    char *text1 = getString(&len, file1, EOF);
    if (text1 == NULL)
    {
        fclose(file1);
        fclose(file2);
        return false;
    }

    char *text2 = getString(&len, file2, EOF);
    if (text2 == NULL)
    {
        free(text1);
        fclose(file1);
        fclose(file2);
        return false;
    }

    fclose(file1);
    fclose(file2);
    const bool result = (strcmp(text1, text2) == 0);
    free(text1);
    free(text2);

    return result;
}

static const bool testCase(char const *const inputFileName, char const *const answerFileName,
                           const char *const *const names, const char *const *const numbers, size_t testSize)
{
    PhoneBook *phoneBook = createPhoneBook();
    if (phoneBook == NULL)
    {
        return false;
    }

    if (readFromDataBase(phoneBook, inputFileName) != ok)
    {
        deletePhoneBook(phoneBook);
        return false;
    }

    ErrorCode errorCode = ok;

    for (size_t i = 0; i < testSize; i++)
    {
        errorCode = addEntry(phoneBook, names[i], numbers[i], true);
        if (errorCode != ok)
        {
            deletePhoneBook(phoneBook);
            return false;
        }
    }
    errorCode = saveToDataBase(phoneBook, OUTPUT_FILE_NAME);
    deletePhoneBook(phoneBook);

    return errorCode == ok && compareFiles(OUTPUT_FILE_NAME, answerFileName);
}

const bool test(void)
{
    const size_t testSize1 = 5;
    const char *const fileName1 = "../tests/testFile1.txt";
    const char *const answerFileName1 = "../tests/answerFile1.txt";
    const char *const names1[5] = {"ddd", "sda", "ada", "sfavdc", "faa"};
    const char *const numbers1[5] = {"243", "5432", "744", "543", "32423"};
    const bool testCase1 = testCase(fileName1, answerFileName1, names1, numbers1, testSize1);

    const size_t testSize2 = 3;
    const char *const fileName2 = "../tests/testFile2.txt";
    const char *const answerFileName2 = "../tests/answerFile2.txt";
    const char *const names2[3] = {"vsvcx", "gza", "gadfc"};
    const char *const numbers2[3] = {"8575", "867", "465"};
    const bool testCase2 = testCase(fileName2, answerFileName2, names2, numbers2, testSize2);

    return testCase1 && testCase2;
}
