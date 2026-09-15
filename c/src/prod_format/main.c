 #include<stdio.h>

int main(void)
{
	int item_number, m, d, y;
	float unit_price;

	printf("Please enter item number: ");
	scanf("%d", &item_number);

	printf("Enter unit price: ");
	scanf("%5f", &unit_price);

	printf("Enter purchase date (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &m, &d, &y);

	printf("Item\tUnit\n\tPrice\t\tDate\n");
	printf("%d\t$%.2f\t%8d/%d/%d\n", item_number, unit_price, m, d, y);

	return 0;
}
