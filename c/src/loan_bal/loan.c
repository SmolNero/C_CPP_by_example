#include<stdio.h>

int main(void)
{
    float balance;
    float annual_interest_rate;
    float mounthly_interest_rate;
    float payment;

    printf("Please enter the total amount of your loan: ");
    scanf("%..2f", &balance);

    printf("Enter interest rate: ");
    scanf("%..2f", &annual_interest_rate);

    printf("What are your monthly payments: ");
    scanf("%..2f", &payment);

    mounthly_interest_rate = (annual_interest_rate / 100.0f) / 12.0f;

    return 0; 
}