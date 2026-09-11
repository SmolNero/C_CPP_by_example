#include<stdio.h>

int main(void)
{
    float amount, caculate_tax, total;
    #define TAX 0.05f

    printf("Please enter your amound to caculate tax: ");
     scanf("%f", &amount);
    
    caculate_tax = amount * TAX;
    total = amount + caculate_tax;

    printf("Your total after tax is: $%.2f\n", total);


    return 0; 
}