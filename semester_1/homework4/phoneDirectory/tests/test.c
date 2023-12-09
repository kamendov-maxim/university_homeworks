#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "../String/String.h"

#define OUTPUT_FILE_NAME "outputFile.txt"

static const bool compareFiles(char const *const filename1, char const *const filename2)
{
    FILE *file1 = fopen(filename1, "r");
    if (file1 == NULL)
    {
        return false;
    }

    FILE *file2 = fopen(filename1, "r");
    if (file2 == NULL)
    {
        fclose(file1);
        return false;
    }

    size_t entriesNumber1 = 0;
    if (fscanf(file1, "%lu\n", &entriesNumber1) != 1)
    {
        fclose(file1);
        fclose(file2);
        return readingFileError;
    }

    size_t entriesNumber2 = 0;
    if (fscanf(file2, "%lu\n", &entriesNumber2) != 1)
    {
        fclose(file1);
        fclose(file2);
        return readingFileError;
    }

    if (entriesNumber1 != entriesNumber2)
    {
        fclose(file1);
        fclose(file2);
        return readingFileError;
    }

    size_t len = 0;
    for (size_t i = 0; i < entriesNumber1; ++i)
    {
        char *line1 = getString(&len, file1, '\n');
        if (line1 == NULL)
        {
            fclose(file1);
            fclose(file2);
            return readingFileError;
        }

        char *line2 = getString(&len, file2, '\n');
        if (line2 == NULL)
        {
            free(line1);
            fclose(file1);
            fclose(file2);
            return readingFileError;
        }

        if (strcmp(line1, line2) != 0)
        {
            free(line1);
            free(line2);
            fclose(file1);
            fclose(file2);
            return readingFileError;
        }
        free(line1);
        free(line2);
    }
    fclose(file1);
    fclose(file2);

    return true;
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
    if (errorCode != ok)
    {
        deletePhoneBook(phoneBook);
        return false;
    }

    deletePhoneBook(phoneBook);
    return compareFiles(OUTPUT_FILE_NAME, answerFileName);
}

const bool test(void)
{
    const size_t testSize1 = 5;
    const char * const fileName1 = "testFile1.txt";
    const char * const answerFileName1 = "answerFile1.txt";
    const char * const names1[5] = {"ddd", "sda", "ada", "sfavdc", "faa"};
    const char * const numbers1[5] = {"243", "5432", "744", "543", "32423"};
    const bool testCase1 = testCase(fileName1, answerFileName1, names1, numbers1, testSize1);
    
    const size_t testSize2 = 3;
    const char * const fileName2 = "testFile2.txt";
    const char * const answerFileName2 = "answerFile2.txt";
    const char * const names2[3] = {"vsvcx", "gza", "gadfc"};
    const char * const numbers2[3] = {"8575", "867", "465"};
    const bool testCase2 = testCase(fileName2, answerFileName2, names2, numbers2, testSize2);
    
    return testCase1 && testCase2;
}