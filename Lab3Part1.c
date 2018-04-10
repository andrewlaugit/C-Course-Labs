#include <stdio.h>
#include <stdbool.h>

/* main functions
 * - takes in the number of cents from the user 
 * - computes the coin denominations needed to make this total
 * - displays the number of each coin needed
 * 
 * List of Variables
 * inputMoney - the total amount of money inputted from the user <type int>
 * quarters - the number of quarters making up the total amount of money <type int>
 * dimes - the number of dimes making up the total amount of money <type int>
 * nickels - the number of nickels making up the total amount of money <type int>
 * cents - the number of cents making up the total amount of money <type int>
 * moneyLeft - the amount of money left after removing a coin <type int>
 * firstCoin - determines whether the coin is the first coin to appear <type Boolean>
 * QUARTERVAL - the value of a quarter <type int>
 * DIMEVAL - the value of a dime <type int>
 * NICKELVAL - the value of a nickel <type int>
 */
int main(void){
    int inputMoney,quarters,dimes,nickels,cents,moneyLeft;
    const int QUARTERVAL=25;
    const int DIMEVAL=10;
    const int NICKELVAL=5;
    bool firstCoin=false;
    
    //repeats the block code until break is called
    while(true){
        //prompts user to input the amount of money they have
        printf("Please give an amount in cents less than 100: ");
        //accepts and save user input
        scanf("%d",&inputMoney);
        
        //calculate the number of each coin needed to make up the total
        if (inputMoney>0 && inputMoney<100){
            firstCoin=true;
            moneyLeft=inputMoney;
            quarters=moneyLeft/QUARTERVAL;
            moneyLeft=moneyLeft%QUARTERVAL;
            dimes=moneyLeft/DIMEVAL;
            moneyLeft=moneyLeft%DIMEVAL;
            nickels=moneyLeft/NICKELVAL;
            moneyLeft=moneyLeft%NICKELVAL;
            cents=moneyLeft;
        } else { //if input is no within 0 and 100
            printf("Goodbye.\n");
            return 0;
        }
        
        //print the number of cents inputted by the user with correct plurality
        printf("%d cents: ",inputMoney);

        //print out the number of quarters with correct plurality
        if (quarters>1){
            printf("%d quarters",quarters);
            firstCoin=false;
        } else if (quarters==1){
            printf("%d quarter",quarters);
            firstCoin=false;
        }
                
        //print out the number of dimes with correct plurality
        if (firstCoin==false && dimes!=0){
            printf(",");
        }
        if (dimes>1){
            printf(" %d dimes",dimes);
            firstCoin=false;
        } else if (dimes==1) {
            printf(" %d dime",dimes);
            firstCoin=false;
        }
        
        //print out the number of dimes with correct plurality
        if (firstCoin==false && nickels!=0){
            printf(",");
        }
        if (nickels>1){
            printf(" %d nickels",nickels);
            firstCoin=false;
        } else if (nickels==1) {
            printf(" %d nickel",nickels);
            firstCoin=false;
         }        
        
        //print out the number of dimes with correct plurality
        if (firstCoin==false && cents!=0){
            printf(",");
        }
        if (cents>1){
            printf(" %d cents",cents);
            firstCoin=false;
        } else if (cents==1) {
            printf(" %d cent",cents);
            firstCoin=false;
        }
        
        printf(".\n"); //prints a period and skips to next line
    } //end of while loop
} //end of main function
