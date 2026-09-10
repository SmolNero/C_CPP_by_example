/* Computes the dimensional weight of a 12" x 10" x 8" box */
#include<stdio.h>

int main(void){
    int height, length, width, volume, weight;

    printf("Enter height of box: ");
    scanf("%d", &height);
    printf("Enter length of box: ");
    scanf("%d", &length);
    printf("Enter width of box: "); 
    scanf("%d", &width);

    volume = height * length * width;
    weight = (volume + 165) / 166; 

    printf("Total Volume(Cubic inches): %d\n", volume);
    printf("Total Weight (Pounds): %d\n", weight);

  return 0;
}
