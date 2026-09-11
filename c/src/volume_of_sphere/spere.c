#include<stdio.h> 

int main()
{
    // radius identifier stores 10 meter radius
    float radius;

    printf("Please enter the radius of the sphere: \n");
     scanf("%f", &radius);

    float pi = 3.14159f;
    float volume = (4.0f / 3.0f)  // V=3/4πr3
     * pi
     * radius
     * radius
     * radius;

     printf("Volume: %.2f cubic meters\n", volume);

    return 0;
}