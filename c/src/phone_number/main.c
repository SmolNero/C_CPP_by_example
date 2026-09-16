// Program that displays phone numbers
#include<stdio.h>

int main()
{
	int area_code, three_digits, four_digits;

	printf("Please enter phone number [ex:(xxx) xxx-xxxx]: ");
	scanf("(%d)%d-%d", &area_code, &three_digits, &four_digits);

	printf("You entered: %d.%d.%d\n", area_code, three_digits, four_digits);

  return 0;
}
