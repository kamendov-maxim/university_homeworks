#include <stdio.h>
#include <stdbool.h>

int main()
{
    printf("Enter the line that consists only of opening '(' and closing ')' round brackets:\n");
    
    char ch = 'A';
    bool flagOfInorrectInput = false;
    bool flagForCorrectBracketLine = true;
    int counter = 0;
    do
    {
        ch = getchar();

        if (ch != '(')
        {
            if (ch != ')')
            {
                if (ch != '\n')
                {
                    flagOfInorrectInput = true;
                }
            }
            else
            {
                counter--;
            }
        }
        else
        {
            counter++;
        }

        if (counter < 0)
        {
            flagForCorrectBracketLine = false;
        }

    } while (ch != '\n');

    if (counter != 0)
    {
        flagForCorrectBracketLine = false;
    }

    if (flagOfInorrectInput)
    {
        printf("There are unavaliable characters in your line\n");
        return 0;
    }

    if (flagForCorrectBracketLine)
    {
        printf("Your bracket line is correct\n");
        return 0;
    }

    printf("Your bracket line is incorrect\n");
    return 0;
}