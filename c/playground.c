#include<stdio.h>

int main()
{

    int amount = 297, twenties;

    printf("I handed the cashier $%d\n",amount);

    amount = amount / 20;

    twenties = amount % 20;

    printf("I am now left with: $%d\n", twenties);

 return 0;
}