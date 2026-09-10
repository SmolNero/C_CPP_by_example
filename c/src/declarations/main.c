#include<stdio.h>

int main(void){

    /*OG variabes*/ 
    float profit;
    int height = 8;
    int id = 27833;
    
   /*changing the values of vars*/  
    profit = 3.99; 
    height = 20;
    
    float humanSum = profit * height;
    float const myKey = humanSum; 
    
    /*printing an int*/
    printf("ID number: %d\n", id);
    
    /*printing an float - displays 4 digit after decimal*/
    printf("Your perm key is: %.4f\n", myKey); 
}
