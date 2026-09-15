#include<stdio.h>

#define TAX 0.05f

int main(void)
{
    float amount, caculate_tax, total;

    printf("Please enter your amount to caculate tax: $");
     scanf("%f", &amount);
    
    total = (amount * TAX) + amount;

    printf("Your total after tax is: $%.2f\n", total);

    return 0; 
}w