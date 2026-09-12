#include<stdio.h>

int main(void)
{
    float x, polynomial;

     printf("Enter in a value for x: ");
     scanf("%f", &x);
    
     //Using Horners Rule
     //polynomial = ((((3 * x + 2) * x - 5) * x - 1) * x + 7) * x - 6;      

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

/*
3
Multiply by x:
3x
Add 2:
3x + 2
Multiply that whole result by x:
(3x + 2)x
Subtract 5:
(3x + 2)x - 5
Multiply that whole result by x:
((3x + 2)x - 5)x
Subtract 1:
((3x + 2)x - 5)x - 1
Multiply again:
(((3x + 2)x - 5)x - 1)x
Add 7:
(((3x + 2)x - 5)x - 1)x + 7
Multiply again:
((((3x + 2)x - 5)x - 1)x + 7)x
Finally subtract 6:
((((3x + 2)x - 5)x - 1)x + 7)x - 6
*/