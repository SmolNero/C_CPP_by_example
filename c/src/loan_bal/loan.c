#include<stdio.h>

int main(void)
{
    float balance;
    float annual_interest_rate;
    float mounthly_interest_rate;
    float payment;

    printf("Please enter the total amount of your loan: ");
    scanf("%f", &balance);

    printf("Enter interest rate: ");
    scanf("%f", &annual_interest_rate);

    printf("What are your monthly payments: ");
    scanf("%f", &payment);

    mounthly_interest_rate = (annual_interest_rate / 100.0f) / 12.0f;
    balance = balance + (balance * mounthly_interest_rate) - payment;

    printf("Balance remaining after first payment: $%.2f\n", balance);

    balance = balance + (balance * mounthly_interest_rate) - payment;

    printf("Balance remaining after second payment: $%.2f\n", balance);
   
    balance = balance + (balance * mounthly_interest_rate) - payment;

    printf("Balance remaining after third payment: $%.2f\n", balance);

    return 0; 
}