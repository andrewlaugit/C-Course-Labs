#include <stdio.h>
#include <stdbool.h>

/* main function
 * - takes in two numbers from the user and an operator character
 * - computes the equation using the operator listed
 * - dislays the answer and the input to two decimal places
 * 
 * List of Variables
 * num1 - the first number inputted by the user <type double>
 * num2 - the second number inputted by the user <type double>
 * answer - the result of computing num1 and num2 with the operator <type double>
 * operator - the operator inputted by the user, must be a,s,m,d <type char>
 */
 
int main(void){
    double num1,num2,answer;
    char operator;
    
    //prompts user to imput two numbers and an operator
    //accepts and stores user input
    printf("Enter first number: ");
    scanf("%lf",&num1);
    printf("Enter second number: ");
    scanf("%lf",&num2);
    printf("Enter calculation command (one of a, s, m, or d): ");
    scanf(" %c",&operator);
        
    //determine which operator was inputted and perform the operation
    //display error messages for divide 0 and invalid operators
    if(operator=='a'){ //addition
        answer=num1+num2;
        printf("Sum of %.2lf and %.2lf is %.2lf\n",num1,num2,answer);
    } else if(operator=='s'){ //subtraction
        answer=num1-num2;
        printf("Difference of %.2lf from %.2lf is %.2lf\n",num1,num2,answer);
    } else if(operator=='m'){ //multiplication
        answer=num1*num2;
        printf("Product of %.2lf and %.2lf is %.2lf\n",num1,num2,answer);
    } else if(operator=='d'){ //division
        if (num2!=0){ //calculates quotient only if denominator is not 0
            answer=num1/num2;
            printf("Division of %.2lf by %.2lf is %.2lf\n",num1,num2,answer);
        } else { //num2==0
            printf("Error, trying to divide by zero\n"); //error message
        }
    } else { //operator not a, s, m, or d
        printf("Error, unknown calculation command given\n"); //error message
        return 0; //ends function
    } //end of if(operator)
    
	return 0; //returns 0 to end function
} //end of main function