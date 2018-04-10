#include <stdio.h>

//forward declaration of functions
void triangle();
int choose();
int factorial();
void spaces();
void indent();

/* main function
 * -prompts user to enter number of rows
 * -calls triangle function to draw pascals triangle
 * -repeats until negative numer is entered
 * 
 * List of Variables
 * numRows - the number of rows in the triangle <type Integer>
 */
int main(void){
    int numRows;
    do{
        //prompt and accept user to enter num of rows
        printf("Enter the number of rows: ");
        scanf("%d",&numRows);
        if(numRows>0){
            triangle(numRows);
        } //end if(numRows>0)
    } while(numRows>=0);
	return 0;
} //end main function

/* triangle function
 * -outputs pascals triangle with correct formatting
 * 
 * List of Variables
 * chooseValue- the value of triangle element <type Integer>
 * 
 * @param rows - the number of rows in the triangle <type Integer>
 */
void triangle(int rows){
    int chooseValue;

    //for loop for each row in the triangle
    for (int row=0;row<=rows-1;row++){
        //calls indent function to indent first number
        indent(row,rows-1);
        
        //for loop for each number on row
        for (int col=row;col>=0;col--){
            //calls choose to find number to be displayed
            chooseValue=choose(row,col);
            printf("%d",chooseValue); //prints the number
            spaces(chooseValue); //calls spaces for spaces after number
        } //end for(col)
        
        printf("\n"); //new line
        
    } //end for(row)
}//end triangle function

/* choose function
 * -determines the combination value of nCr
 * 
 * List of Variables
 * output - the value of nCr <type Integer>
 */
int choose(int n, int r){
    int output;
    output=factorial(n)/(factorial(r)*factorial(n-r));
    return output;    
} //end choose function

/* factorial function
 * -finds the value of n factorial (n!) 
 * 
 * List of Variables
 * outout - the value of n! <type Integer>
 */
int factorial(int n){
    int output=1;
    
    if (n>0){
        //for loop from n to 1
        for(int i=n;i>=1;i--){
            output=output*i;
        } //end for
    } //end if(n>0)
    
    return output;
} //end factorial function

/* spaces function
 * -determines the length of number
 * -prints the appropriate number of spaces
 * 
 * List of Variables
 * spaceCount - the number of spaces needed <type Integer>
 * 
 * @param number - the number before the spaces <type Integer>
 */
void spaces(int number){
    int spaceCount=5;
    
    //repeats until length found
    while(number!=0){
        number=number/10;
        if (number!=0){
            spaceCount=spaceCount-1;
        } else {
            break;
        } //end if/else
    } //end while
    
    //prints spaceCount spaces
    for (int i=1;i<=spaceCount;i++){
        printf(" "); //prints a space
    } //end for
} //end spaces function

/* indent function
 * -indents the first element of each line by appropriate amount
 * 
 * List of Variables
 * totalSpaces - the number of spaces needed before first number on row <type Integer>
 * 
 * @param row - the row number of the triangle <type Integer>
 * @param total - the total number of rows in the triangle <type Integer>
 */
void indent(int row, int total){
    int totalSpaces;
    
    //set total indent
    totalSpaces=(total-row)*3;
    
    for (int i=1;i<=totalSpaces;i++){
        printf(" ");
    } //end for
} //end indent function