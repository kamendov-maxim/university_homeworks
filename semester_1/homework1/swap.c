#include <stdio.h>

int main() 
{
    
    int variable1 = 1;
    int variable2 = 2;
    
    printf("Before values of the variables were swapped: variable1 = %d, variable2 = %d\n", variable1, variable2);

    variable1 += variable2;
    variable2 -= variable1;
    variable2 *= -1;
    variable1 -= variable2;

    printf("After: variable1 = %d, variable2 = %d\n", variable1, variable2);
    
    return 0;

}


