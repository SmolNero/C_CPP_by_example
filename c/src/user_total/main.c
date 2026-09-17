/*this program takes the price of 3 items and applies tax, presenting the total*/
#include<stdio.h>

int main(void)
{
	float x,y,z;
	
	#define TAX 0.05f
	#define USER_SUM x + y + z
	#define TOTAL (TAX * USER_SUM) + USER_SUM

	printf("Welcome, now pick 3 numbers: \n");

	scanf("%f \n%f \n\n%f", &x, &y, &z);

	printf("With tax, you sum total is: $%.2f\n", TOTAL);

	return 0;
}
