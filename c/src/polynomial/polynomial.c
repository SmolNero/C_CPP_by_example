#include<stdio.h>

int main(void)
{
    float x, polynomial;

     printf("Enter in a value for x: ");
     scanf("%f", &x);
    
    // Using Horners Rul 
    // polynomial = ((((3 * x + 2) * x - 5) * x - 1) * x + 7) * x - 6;      
     polynomial = 
     (3 * x * x * x * x * x) 
     + (2 * x * x * x * x)
     - (5 * x * x * x)
     - (x * x)
     + (7 * x)
     - 6;
    
    printf("Polynomial is: %.2f\n", polynomial);

    return 0;
}