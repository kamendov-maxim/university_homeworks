
#include "findComments.h"
#include "readFile.h"
#include "list.h"
#include "../../String/String.h"

typedef enum State
{
    start,
    firstSlash,
    firstStar,
    text,
    secondStar,
    finish
} State;

State move(State state, char c)
{
    switch (state)
    {
    case start:
    {
        if (c == '/')
        {
            return firstSlash;
        }
        return start;
    }

    case firstSlash:
    {
        if (c == '*')
        {
            return firstStar;
        }
        return start;
    }

    case firstStar:
    {
        if (c == '*')
        {
            return secondStar;
        }
        return text;
    }

    case text:
    {
        if (c == '*')
        {
            return secondStar;
        }
        return text;
    }

    case secondStar:
    {
        if (c == '/')
        {
            return finish;
        }
        return text;
    }

    default:
        return start;
        break;
    }
}

ErrorCode addComment(List *list, size_t start, size_t end, const char *const text)
{
    char *string = malloc((start + end + 1) * sizeof(char));
    if (string == NULL)
    {
        return memoryError;
    }

    for (size_t i = start; i < end + 1; ++i)
    {
        string[i - start] = text[i];
    }

    ErrorCode ec = addElement(list, string);
    if (ec != ok)
    {
        free(string);
    }

    return ec;
}

char **findComments(const char *const fileName, size_t *outputLen)
{
    List *list = createList();
    if (list == NULL)
    {
        return NULL;
    }

    size_t len = 0;
    char *text = readFile(fileName, &len);
    if (text == NULL)
    {
        free(list);
        return NULL;
    }

    State state = start;
    size_t currentCommentStart = 0;
    size_t currentCommentEnd = 0;
     for (size_t i = 0; i < len; i++)
    {
        state = move(state, text[i]);
        if (state == firstSlash)
        {
            currentCommentStart = i;
        }
        if (state == finish)
        {
            currentCommentEnd = i;
            if (addComment(list, currentCommentStart, currentCommentEnd, text) != ok)
            {
                free(text);
                deleteList(&list);
                return NULL;
            }
        }
    }
    free(text);
    char **output = writeToDefaultArray(list, outputLen);
    deleteList(&list);
    return output;
}
