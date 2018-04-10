#include <stdio.h>

//forward declare functions in program
int askNumRows();
void drawTriangle(int rows);

/* main function
 * -calls functions to accept the number of rows in a triangle
 *  and  calls a function to draw triangle using '^'
 * 
 * Variables
 * numRows - the number of rows in the triangle <type Integer>
 */ 
int main(void){
    int numRows;
    
    //assigns the number of rows to return value from askNumRows()
    numRows=askNumRows();
    //calls drawTriangle and sends numRows as arguement
    drawTriangle(numRows);
    
	return 0;
} //end of main function

/* drawTriangle function
 * -draws a triangle using '^' character
 * 
 * @param rows - the number of rows in the triangle
 * @return void
 */
void drawTriangle(int rows){
    //for loop for number of rows
    for(int r=1;r<=rows;r++){
        //for loop for number of columns needed
        for (int c=1; c<=rows*2-1;c++){
            
            //row+column equals total rows+1 where ^ should exist
            //row-column equals total rows-1 where ^ should exist
            if(c+r==rows+1||c-r==rows-1){
                printf("^");
            } else if(r==rows){ //prints ^ for all columns on last row
                printf("^");
            } else { //prints spaces in columns where ^ doesnt exist
                printf(" ");
            } //end if/else
            
        } //end for loop columns
        
        printf("\n"); //skips a line
    } //end for loop rows
} //end drawTriangle function

/* askNumRows function
 * -accepts user input of type int
 * -returns the number of rows in the triangle
 * 
 * Variables
 * numRowsEntered - user input of the number of rows <type int>
 * 
 * @return numRowsEntered - number of rows entered by user
 */
int askNumRows(){
    int numRowsEntered;
    
    //prompts user to enter number of rows and accepts it
    printf("Enter the number of rows in the triangle: ");
    scanf("%d",&numRowsEntered);
    
    //returns user input
    return numRowsEntered;
} //end askNumRows function
