#include<stdio.h>

int main(void){

    /*OG variabes*/ 
    int height = 0;
    int id = 27833;
    
   /*changing the values of vars*/  
    height = 20;
    
    float humanSum = id * height;
    float const profit = humanSum; 
    
    /*printing an int*/
    printf("ID number: %d\n", id);
    
    /*printing an float - displays 4 digit after decimal*/
    printf("Your profit is: %.2f\n", profit);

    printf("Both height: %d & id: %d\n", height, id);
}
