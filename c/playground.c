#include<stdio.h>

int main(void)
{
 	int i;
 	float x;

 	i = 40;
 	x = 839.21f;

 	//printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
 	//printf("|%10.3f|%10.3e|%-10g|\n", x , x, x);

 	// output:
	// |40|   40|40   |  040|
	// |   839.210| 8.392e+02|839.21    |

 	// \a makes the machine produce a simple sound
 	//printf("Bing\a");

 	printf("Item\tUnit\tPurchase\n\tPrice\tDate\n");
 	printf("\"String within a string\"\n");

 	printf("\\");

	return 0;
}