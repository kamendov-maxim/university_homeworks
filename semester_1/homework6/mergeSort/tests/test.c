#include <stdbool.h>

#include "test.h"
#include "../../list/list.h"

static bool test1(void)
{
    ListErrorCode listErrorCode = ok;
    List *testList1 = createList(&listErrorCode);
    if (listErrorCode != ok)
    {
        return false;
    }

    listErrorCode = append(testList1, "bbb", "3");
    if (listErrorCode != ok)
    {
        return false;
    }

    listErrorCode = append(testList1, "aaa", "2");
    if (listErrorCode != ok)
    {
        return false;
    }

    listErrorCode = append(testList1, "ccc", "5");
    if (listErrorCode != ok)
    {
        return false;
    }

    listErrorCode = append(testList1, "eee", "4");
    if (listErrorCode != ok)
    {
        return false;
    }

    listErrorCode = append(testList1, "ddd", "1");
    if (listErrorCode != ok)
    {
        return false;
    }

    mergeSortByNumber(testList1);
    if (!isSortedByNumber(testList1))
    {
        deleteList(testList1);
        return false;
    }
    mergeSortByName(testList1);
    if (!isSortedByName(testList1))
    {
        deleteList(testList1);
        return false;
    }
    deleteList(testList1);

    return true;
}

static bool test2(void)
{
    ListErrorCode listErrorCode = ok;
    List *testList2 = createList(&listErrorCode);
    if (listErrorCode != ok)
    {
        return false;
    }

    listErrorCode = append(testList2, "eee", "5");
    if (listErrorCode != ok)
    {
        return false;
    }
    listErrorCode = append(testList2, "ddd", "4");
    if (listErrorCode != ok)
    {
        return false;
    }
    listErrorCode = append(testList2, "ccc", "3");
    if (listErrorCode != ok)
    {
        return false;
    }
    listErrorCode = append(testList2, "bbb", "2");
    if (listErrorCode != ok)
    {
        return false;
    }
    listErrorCode = append(testList2, "aaa", "1");
    if (listErrorCode != ok)
    {
        return false;
    }
    mergeSortByNumber(testList2);
    if (!isSortedByNumber(testList2))
    {
        deleteList(testList2);
        return false;
    }
    mergeSortByName(testList2);
    if (!isSortedByName(testList2))
    {
        deleteList(testList2);
        return false;
    }
    deleteList(testList2);

    return true;
}

static bool test3(void)
{
    ListErrorCode listErrorCode = ok;
    List *testList3 = createList(&listErrorCode);
    if (listErrorCode != ok)
    {
        return false;
    }

    listErrorCode = append(testList3, "aaa", "1");
    if (listErrorCode != ok)
    {
        return false;
    }
    listErrorCode = append(testList3, "aaa", "1");
    if (listErrorCode != ok)
    {
        return false;
    }
    listErrorCode = append(testList3, "aaa", "1");
    if (listErrorCode != ok)
    {
        return false;
    }
    listErrorCode = append(testList3, "aaa", "1");
    if (listErrorCode != ok)
    {
        return false;
    }
    listErrorCode = append(testList3, "aaa", "1");
    if (listErrorCode != ok)
    {
        deleteList(testList3);
        return false;
    }
    mergeSortByNumber(testList3);
    if (!isSortedByNumber(testList3))
    {
        deleteList(testList3);
        return false;
    }
    mergeSortByName(testList3);
    if (!isSortedByName(testList3))
    {
        printf("Failed on sorting by a name (all elements are the same)\n");
        return false;
    }
    deleteList(testList3);

    return true;
}

bool test(void)
{
    return test1() && test2() && test3();
}