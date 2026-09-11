#include<stdio.h>

int main(void){
    int age, id_number;
    #define POSITION_CALC 1.32455

    printf("Welcome! To determine your position. Please enter the following, starting with your age\n");
     scanf("%d", &age);
    printf("Thank you! Next, your employee ID number:\n");
     scanf("%d", &id_number);
    
    float employee_standing = age * id_number * POSITION_CALC;
    
    printf("Your current position is: %.6f\n", employee_standing);

    return 0;
}