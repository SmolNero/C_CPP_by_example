#include<stdio.h>

#define INCHES_PER_POUND 32
int pounds = 170, volume = 12;

int main()
{
    printf("Dimensional weight (pounds): %d\n", 
        (volume + INCHES_PER_POUND - 1) * INCHES_PER_POUND);

    return 0;
}