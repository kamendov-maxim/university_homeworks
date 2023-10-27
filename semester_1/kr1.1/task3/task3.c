#include <stdio.h>
#include <stdbool.h>

#define SIZE 1000

bool test();
int countSymbols(const char *filename, int count[]);
void consoleOutput(int count[]);
bool test(void);
bool test1(void);
bool test2(void);
bool test3(void);

int main(void)
{
    if (!test())
    {
        printf("Sorry but it seems like the program doesnt work correctly\n");
        return 1;
    }

    int count[SIZE] = {0};
    int errorCode = countSymbols("file.txt", count);
    if (errorCode == 1)
    {
        printf("There is no such file\n");
        return 1;
    }
    consoleOutput(count);
    return 0;
}

int countSymbols(const char *filename, int count[])
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        return 1;
    }

    while (!feof(file))
    {
        char currentCharacter = fgetc(file);
        ++count[currentCharacter];
    }

    fclose(file);

    return 0;
}

void consoleOutput(int count[])
{
    for (int i = 0; i < SIZE; ++i)
    {
        if (count[i] > 0)
        {
            switch (i)
            {
            case '\n':
            {
                printf("Line break symbol appears in the line %d times\n", count[i]);
                break;
            }

            case ' ':
            {
                printf("Space symbol appears in the line %d times\n", count[i]);
                break;
            }

            default:
            {
                printf("%c symbol appears in the line %d times\n", i, count[i]);
                break;
            }
            }
        }
    }
}

bool test(void)
{
    return (test1() && test2() && test3());
}

bool test1(void)
{
    int count[SIZE] = {0};
    int errorCode = countSymbols("test1.txt", count);
    if (errorCode == 1)
    {
        return false;
    }

    if (count['a'] != 3 || count['b'] != 3 || count[' '] != 3 || count['\n'] != 3)
    {
        return false;
    }

    return true;
}


bool test2(void)
{
    int count[SIZE] = {0};
    int errorCode = countSymbols("test2.txt", count);
    if (errorCode == 1)
    {
        return false;
    }

    for (int i = 0; i < SIZE; ++i)
    {
        if (count[i] != 0)
        {
            return false;
        }
    }

    return true;
}

bool test3(void)
{
    int count[SIZE] = {0};
    int errorCode = countSymbols("test3.txt", count);
    if (errorCode == 1)
    {
        return false;
    }

    if (count['|'] != 3 || count['\\'] != 3 || count[';'] != 2 || count[':'] != 2)
    {
        return false;
    }

    return true;
}