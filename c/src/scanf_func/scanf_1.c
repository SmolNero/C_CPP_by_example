#include<stdio.h>

int main()
{
	int i, j;
	float x, y;

	printf("Please enter in two ints and two floats:\n");
	scanf("%d%d%f%f", &i, &j, &x, &y);

	printf(" User input -> | %d | %d | %10.3f | %10.3e", i, j, x, y);

	// *****	
	//printf(" User input -> | %d | %d | %f | %f\n", i, j, x, y);
	//OUTPUT: User input -> | 2 | 5 | 23.000000 | 65.000000
	// ***** 
	//printf(" User input -> | %d | %d | %f | %f\n", i, j, x, y);
	//OUTPUT: User input -> | 32 | 4 | 0.300000 | -4000
	// *****
	//printf(" User input -> | %d | %d | %10.3f | %10.3e", i, j, x, y);
	//OUTPUT:  User input -> | 32 | 33 |      0.300 | -4.000e+00% 
	// *****
	
	return 0;
}
