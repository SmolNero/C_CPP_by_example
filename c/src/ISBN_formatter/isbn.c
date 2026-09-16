#include<stdio.h>

int main(void)
{
	int gs1, group_identifier, publisher_code, item_num, check_digit;

	printf("Please enter ISBN number: ");
	scanf("%d-%d-%d-%d-%d", &gs1, &group_identifier, &publisher_code, &item_num, &check_digit);
	printf("GS1 prefix: %d\n", gs1);
	printf("Group identifier: %d\n", group_identifier); 
	printf("Publisher code: %d\n", publisher_code); 
	printf("Item number: %d\n", item_num); 
	printf("Check digit: %d\n", check_digit);  

	return 0;
}


