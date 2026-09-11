/*Converts from faranheight to celsius*/
#include<stdio.h>

#define FREEZING_PT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)

int main(void)
{
    float farenheit, celsius; 

    printf("Please ender farenheit temperature: ");
      scanf("%f", &farenheit);       

    celsius = (farenheit - FREEZING_PT) * SCALE_FACTOR;

    printf("Cesius equivalant: %.2f\n", celsius);

    return 0;
}