#include<stdio.h>

int main(void)
{

	int n1, n2, n3, n4;
	int n5, n6, n7, n8;
	int n9, n10, n11, n12;
	int n13, n14, n15, n16;

	printf("Enter the numbers from 1 to 16 in any order:\n");
	
	scanf(
		"%d %d %d %d "
		"%d %d %d %d "
		"%d %d %d %d "
		"%d %d %d %d",
		&n1, &n2, &n3, &n4,
		&n5, &n6, &n7, &n8,
		&n9, &n10, &n11, &n12,
		&n13,&n14, &n15, &n16 
		);

	// Book: 16 3 2 13 5 10 11 8 9 6 7 12 4 15 14 1
	// 1 2 3 5 13 12 16 4 6 8 7 10 9 11 14 15 

	printf("\n");
	printf("%2d %2d %2d %2d\n", 
		n1, n2, n3, n4);
	printf("%2d %2d %2d %2d\n", 
		n5, n6, n7, n8);
	printf("%2d %2d %2d %2d\n", 
		n9, n10, n11, n12);
	printf("%2d %2d %2d %2d\n",
		n13, n14, n15, n16);

	printf(
		"Row sums: %d %d %d %d\n",
		n1 + n2 + n3 + n4,
		n5 + n6 + n7 + n8,
		n9 + n10 + n11 + n12,
		n13 + n14 + n15 + n16
	);
	
	printf(
		"Column sums: %d %d %d %d\n",
		n1 + n5 + n9 + n13,
		n2 + n6 + n10 + n14,
		n3 + n7 + n11 + n15,
		n4 + n8 + n12 + n16
	);
	
	printf(
		"Diagonal sums: %d %d\n",
		n1 + n6 + n11 + n16,
		n4 + n7 + n10 + n13
	);
	
	return 0; 
}
