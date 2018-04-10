#include <stdio.h>
#include <math.h>

//forward declaration of functions
int convertBinaryToDecimal(int binIn);
int convertDecimalToBinary(int decIn);

/* main function
 * -determines which function is needed
 * -calls appropriate function to perform operation
 * 
 * List of Variables
 * convType - either B or D to determine function needed <type Char>
 * binIn - binary value entered by user <type Integer>
 * decOut- decimal output calculated from binIn <type Integer>
 * decIn - decimal value entered by user <type Integer>
 * binOut - binary value output generated from the decIn value <type Integer>
 */
int main(void){
    char convType;
    int binIn,decOut,decIn,binOut;
    
    //prompts the user to enter the function wanted
	printf("Enter B for conversion of Binary to Decimal, OR\n");
    printf("Enter D for conversion of Decimal to Binary: ");
    scanf("%c",&convType); //accepts a single character
    
    //prompts the user to enter a number
    printf("Enter your number: ");
    
    //determines what function is wanted by user
    if(convType=='B'){ //binary to decimal
        scanf("%d",&binIn); //accepts a binary value
        //send binary to functiona and accept return decimal
        decOut=convertBinaryToDecimal(binIn); 
        printf("%d in binary = %d in decimal",binIn,decOut); //print input and results
    } else if(convType=='D'){ //decimal to binary
        scanf("%d",&decIn); //accepts decimal value
        //send decimal to function and accept return binary
        binOut=convertDecimalToBinary(decIn); 
        printf("%d in decimal = %d in binary",decIn,binOut); //print input and results
    } else { //no function, exit program
        printf("Invalid input; Goodbye"); //error message
    } //end if/else
    
    printf("\n"); //next line
	return 0;
} //end main function

/* convertBinaryToDecimal function
 * -converts binary value to decimal
 * 
 * List of Variables
 * outputDec - decimal value of the binary <type Integer>
 * count - the number of bits in the binary <type Integer>
 * 
 * @param binIn - binary value entered by user <type Integer>
 * @return outputDec - decimal value of the binary input <type Integer>
 */
int convertBinaryToDecimal(int binIn){
    int outputDec=0,count=0;
    
    //repeats until the length of the binary is found
    while(binIn!=0){
        if (binIn%10==1){ //if the last digit is a one
            outputDec=outputDec+pow(2,count); //add 2^count to total
        } //end if
        
        binIn=binIn/10; //remove the last digit from the binary
        count=count+1; //move onto next digit on left
    } //end while
    
    return outputDec;
} //end convertBinaryToDecimal function

/* convertDecimalToBinary function
 * -converts decimal to binary value
 * -determines max length of binary needed
 * 
 * List of Variables
 * decLeft - copy of decimal entered to determine binary length <type double>
 * outputBin - binary value of the decimal <type Integer>
 * count - the number of bits in the binary <type Integer>
 * 
 * @param decIn - decimal entered by user <type Integer>
 * @return outputBin - binary value of the decimal <type Integer>
 */
int convertDecimalToBinary(int decIn){
    double decLeft=(double)decIn;
    int outputBin=0,count=0;
    
    //repeats until max binary length found
    while(decLeft>1.0){
        decLeft=decLeft/2.0; //divides decimal by 2
        count=count+1; //increases max binary length by 1
    } //end while
    
    //starts from leftmost digit of binary
    for(int exponent=count;exponent>=0;exponent--){
        //if decimal value is bigger than the binary value
        if(decIn-pow(2,exponent)>=0){ 
            //add the bianry digit in appropriate position
            outputBin=outputBin+pow(10,exponent); 
            //decrease the decimal value after removing binary value
            decIn=decIn-pow(2,exponent); 
        } //end if
    } //end for
    
    return outputBin;
} //end convertDecimalToBinary function