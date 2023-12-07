#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define PROGRAM_FINISHED_CORRECTLY 0
#define MEMORY_ERROR 1
#define PROGRAM_FAILED_TESTS 2

bool test(void);

static char *getString(size_t *const len, FILE *filename, char const endOfLine)
{
    *len = 0;
    size_t capacity = 1;
    char *s = (char *)malloc(sizeof(char));
    if (s == NULL)
    {
        return NULL;
    }

    for (char c = fgetc(filename); c != endOfLine && c != EOF; c = fgetc(filename))
    {
        s[(*len)++] = c;

        if (*len >= capacity)
        {
            capacity *= 2;
            s = (char *)realloc(s, capacity * sizeof(char));
            if (s == NULL)
            {
                return NULL;
            }
        }
    }

    s[*len] = '\0';

    return s;
}

size_t countSubstings(char const * const string, char const * const subString)
{
    const char *currentPtr = string;
    const char *hit = NULL;
    size_t count = 0;

    for (; (hit = strstr(currentPtr, subString)) != NULL; ++count)
    {
        currentPtr = hit + 1;
    }
    
    return count;
}

int main(void)
{

    if (!test())
    {
        printf("Программа сейчас не работает\n");
        return PROGRAM_FAILED_TESTS;
    }

    size_t len = 0;
    printf("Введите вашу строку: ");
    char * const string = getString(&len, stdin, '\n');
    if (string == NULL)
    {
        exit(MEMORY_ERROR);
    }

    printf("Введите вашу подстроку: ");
    char *const subString = getString(&len, stdin, '\n');
    if (subString == NULL)
    {
        free(string);
        exit(MEMORY_ERROR);
    }

    printf("Количество вхождений подстроки %s в строку %s: %zu\n", subString, string, countSubstings(string, subString));

    free(string);
    free(subString);
    return PROGRAM_FINISHED_CORRECTLY;
}



bool testCase(char const * const string, char const * const subString, size_t answer)
{
    return countSubstings(string, subString) == answer;
}

bool test(void)
{ 
    char const * const testString1 = "aaa";
    char const * const testSubString1 = "a";
    size_t answer1 = 3;
    bool testCase1 = testCase(testString1, testSubString1, answer1);

    char const * const testString2 = "bababa";
    char const * const testSubString2 = "ab";
    size_t answer2 = 2; 
    bool testCase2 = testCase(testString2, testSubString2, answer2);

    char const * const testString3 = "dasfazfadsfafazfaaf";
    char const * const testSubString3 = "zfa";
    size_t answer3 = 2;
    bool testCase3 = testCase(testString3, testSubString3, answer3);

    return testCase1 && testCase2 && testCase3;
}
