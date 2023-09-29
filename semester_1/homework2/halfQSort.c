#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    srand(time(0));

    printf("\nEnter the size of your array: ");
    int size = 0;
    scanf("%d", &size);

    while (size <= 0)
    {
        printf("\nSize of your array should be at least 1\n");
        printf("Enter the size of your array: ");
        scanf("%d", &size);
    }

    int *array = malloc(size * sizeof(int));
    if (array == NULL)
    {
        printf("\nSorry but something went wrong\n");
        return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        array[i] = rand();
    }

}