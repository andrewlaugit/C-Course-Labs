#include <stdio.h> //allows access to input/output library
#include <math.h> //allows access to math library

/* main method
 * 
 * List of Variables
 * num1 - first number the user inputs <type double>
 * num2 - second number the user inputs <type double>
 * num3 - third number the user inputs <type double> 
 * mean - the mean average of the three numbers inputted by user <type double>
 * variance - variance of the 3 number data set <type double>
 * stdDeviation - standard deviation of the three number data set <type double>
 * 
 */

int main(void){
    double num1,num2,num3,mean,variance,stdDeviation;
    
    printf("Enter three numbers: "); //prompts user to enter three numbers
    scanf("%lf %lf %lf",&num1,&num2,&num3); //reads three numbers and stores them
    
    //finds total of the three numbers and divides by 3
    mean = (num1+num2+num3)/3; 
    //finds variance of the numbers
    variance=(pow((num1-mean),2)+pow((num2-mean),2)+pow((num3-mean),2))/2; 
    //calculate standard deviation by taking square root of variance
    stdDeviation = sqrt(variance); 
    //displays mean and standard deviation in correct format
	printf("The mean is %.2lf and the standard deviation is %.2lf\n",mean,stdDeviation);
	return 0;
} //end of Lab1
