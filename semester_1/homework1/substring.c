#include <stdio.h>
#include <stdbool.h>

int countingSubstrings(char *string, char *subString, int lengthOfString, int lengthOfSubstring);
int readingLineFromConsole(char *string);
bool test(void);

int main()
{
    if (!test())
    {
        printf("Sorry but the program does not work correctly\n");
        return 1;
    }
    printf("Enter your string\n");
    char S[1000];
    int lengthOfS = readingLineFromConsole(S);
    printf("Enter your substring\n");
    char S1[1000];
    int lengthOfS1 = readingLineFromConsole(S1);
    int numberOfSubstrings = countingSubstrings(S, S1, lengthOfS, lengthOfS1);

    printf("The number of occurances of your substring in your string is %d\n", numberOfSubstrings);
    return 0;
}

int countingSubstrings(char *string, char *subString, int lengthOfString, int lengthOfSubstring)
{
    int count = 0;
    bool doWeCompareRightNow = false;

    int currentSubstringCharacter = -1;

    for (int currentCharacter = 0; currentCharacter < lengthOfString; ++currentCharacter)
    {
        if (doWeCompareRightNow)
        {
            if (++currentSubstringCharacter < lengthOfSubstring)
            {
                doWeCompareRightNow = (string[currentCharacter] == subString[currentSubstringCharacter] ? true : false);
            }

            if (!doWeCompareRightNow)
            {
                currentSubstringCharacter = -1;
            }
        }

        if (string[currentCharacter] == subString[0] && !doWeCompareRightNow)
        {
            doWeCompareRightNow = true;
            ++currentSubstringCharacter;
        }

        if (currentSubstringCharacter + 1 == lengthOfSubstring && doWeCompareRightNow)
        {
            currentSubstringCharacter = -1;
            doWeCompareRightNow = false;
            ++count;
        }
    }
    return count;
}

int readingLineFromConsole(char *string)
{
    int c = 0;
    char ch;
    do
    {
        ch = getchar();
        string[c] = ch;
        c++;
    } while (ch != '\n');

    c = c - 1;
    string[c] = '\0';
    return c;
}

bool test(void)
{

    char testString1[0] = "";
    char testSubstring1[6] = "fsdffa";
    int testStringLength1 = 0;
    int testSubStringLength1 = 6;
    int answer1 = 0;
    if (!(countingSubstrings(testString1, testSubstring1, testStringLength1, testSubStringLength1) == answer1))
    {
        printf("%d", 1);
        return false;
    }

    char testString2[23] = "afdaasddfgsafasddasdasd";
    char testSubstring2[3] = "asd";
    int testStringLength2 = 23;
    int testSubStringLength2 = 3;
    int answer2 = 4;
    if (!(countingSubstrings(testString2, testSubstring2, testStringLength2, testSubStringLength2) == answer2))
    {
        return false;
    }

    char testString3[9] = "dgaafadfa";
    char testSubstring3[0] = "";
    int testStringLength3 = 9;
    int testSubStringLength3 = 0;
    int answer3 = 0;
    if (!(countingSubstrings(testString3, testSubstring3, testStringLength3, testSubStringLength3) == answer3))
    {
        return false;
    }
    char testString4[5] = "aaaaa";
    char testSubstring4[1] = "a";
    int testStringLength4 = 5;
    int testSubStringLength4 = 1;
    int answer4 = 5;
    if (!(countingSubstrings(testString4, testSubstring4, testStringLength4, testSubStringLength4) == answer4))
    {
        return false;
    }

    char testString5[2] = "bb";
    char testSubstring5[2] = "bb";
    int testStringLength5 = 2;
    int testSubStringLength5 = 2;
    int answer5 = 1;
    if (!(countingSubstrings(testString5, testSubstring5, testStringLength5, testSubStringLength5) == answer5))
    {
        return false;
    }

    return true;
}
