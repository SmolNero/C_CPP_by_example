#include<stdio.h>

int main(void)
{
	int m,d,y;

	printf("Enter in (mm/dd/yyyy: ");
	scanf("%d/%d/%d", &m, &d, &y);

	printf("You entered the date: %d/%d/%d\n", y, m, d);

	return 0;
}
