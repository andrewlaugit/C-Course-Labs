#include <stdio.h>

/* main method
 * - take in 4 band colours from letter colour codes
 * - output band colours
 * - display the resistance level in most appropriate units and
 *   and tolerance of the resistor
 * 
 * List of Variables
 * totalResistance - resistance of the resistor <type double>
 * resistance1 - value of the tens digit of the resistance level <type double>
 * resistance2 - value of the ones digit of the resistance level <type double>
 * multiplier - value of the multiplier of the resistor <type double>
 * tolerance - percent value of the tolerance of the resistor <type double> 
 * band1 - letter of colour code of band1 <type char> 
 * band2 - letter of colour code of band2 <type char> 
 * band3 - letter of colour code of band3 <type char> 
 * band4 - letter of colour code of band4 <type char>
 * 
 * @return void 
 */

int main(void){
    double totalResistance,resistance1,resistance2,multiplier,tolerance;
    char band1,band2,band3,band4;
    
    //prompt and accept user input for band colours
	printf("Please enter the 1st band:\n");
    scanf(" %c",&band1);
    printf("Please enter the 2nd band:\n");
    scanf(" %c",&band2);
    printf("Please enter the multiplier band:\n");
    scanf(" %c",&band3);
    printf("Please enter the tolerance band:\n");
    scanf(" %c",&band4);
    printf("Resistor bands:");
    
    //determine and print first band colour and resistance level
    if(band1=='K' || band1=='k'){
        printf(" Black");
        resistance1=0;
    } else if(band1=='B' || band1=='b'){
        printf(" Brown");
        resistance1=1;
    } else if(band1=='R' || band1=='r'){
        printf(" Red");
        resistance1=2;
    } else if(band1=='O' || band1=='o'){
        printf(" Orange");
        resistance1=3;
    } else if(band1=='E' || band1=='e'){
        printf(" Yellow");
        resistance1=4;
    } else if(band1=='G' || band1=='g'){
        printf(" Green");
        resistance1=5;
    } else if(band1=='U' || band1=='u'){
        printf(" Blue");
        resistance1=6;
    } else if(band1=='V' || band1=='v'){
        printf(" Violet");
        resistance1=7;
    } else if(band1=='Y' || band1=='y'){
        printf(" Gray");
        resistance1=8;
    } else if(band1=='W' || band1=='w'){
        printf(" White");
        resistance1=9;
    } else{
        printf("<Invalid 1st band!>");
    }
    
    //determine second band colour and resistance value
    if(band2=='K' || band2=='k'){
        printf(" Black");
        resistance2=0;
    } else if(band2=='B' || band2=='b'){
        printf(" Brown");
        resistance2=1;
    } else if(band2=='R' || band2=='r'){
        printf(" Red");
        resistance2=2;
    } else if(band2=='O' || band2=='o'){
        printf(" Orange");
        resistance2=3;
    } else if(band2=='E' || band2=='e'){
        printf(" Yellow");
        resistance2=4;
    } else if(band2=='G' || band2=='g'){
        printf(" Green");
        resistance2=5;
    } else if(band2=='U' || band2=='u'){
        printf(" Blue");
        resistance2=6;
    } else if(band2=='V' || band2=='v'){
        printf(" Violet");
        resistance2=7;
    } else if(band2=='Y' || band2=='y'){
        printf(" Gray");
        resistance2=8;
    } else if(band2=='W' || band2=='w'){
        printf(" White");
        resistance2=9;
    } else {
        printf(" <Invalid 2nd band!>");
    }
    
    //determine third band colour and multiplier value
    if(band3=='K' || band3=='k'){
        printf(" Black");
        multiplier=1;
    } else if(band3=='B' || band3=='b'){
        printf(" Brown");
        multiplier=10;
    } else if(band3=='R' || band3=='r'){
        printf(" Red");
        multiplier=100;
    } else if(band3=='O' || band3=='o'){
        printf(" Orange");
        multiplier=1000;
    } else if(band3=='E' || band3=='e'){
        printf(" Yellow");
        multiplier=10000;
    } else if(band3=='G' || band3=='g'){
        printf(" Green");
        multiplier=100000;
    } else if(band3=='U' || band3=='u'){
        printf(" Blue");
        multiplier=1000000;
    } else if(band3=='V' || band3=='v'){
        printf(" Violet");
        multiplier=10000000;
    } else if(band3=='L' || band3=='l'){
        printf(" Gold");
        multiplier=0.1;
    } else if(band3=='S' || band3=='s'){
        printf(" Silver");
        multiplier=0.01;
    } else {
        printf(" <Invalid 3rd band!>");
    }
    
    //determine fourth band colour and tolerance value
    if(band4=='B' || band4=='b'){
        printf(" Brown");
        tolerance=1;
    } else if(band4=='R' || band4=='r'){
        printf(" Red");
        tolerance=2;
    } else if(band4=='G' || band4=='g'){
        printf(" Green");
        tolerance=0.5;
    } else if(band4=='U' || band4=='u'){
        printf(" Blue");
        tolerance=0.25;
    } else if(band4=='V' || band4=='v'){
        printf(" Violet");
        tolerance=0.1;
    } else if(band4=='Y' || band4=='y'){
        printf(" Grey");
        tolerance=0.05;
    } else if(band4=='L' || band4=='l'){
        printf(" Gold");
        tolerance=5;
    } else if(band4=='S' || band4=='s'){
        printf(" Silver");
        tolerance=10;
    } else {
        printf(" <Invalid 4th band!>");
    }
    printf("\n"); //new line
    
    totalResistance = ((resistance1*10)+resistance2)*multiplier; //calculate total resistance
    
    //determine the most appropriate units and output the resistance
    if (totalResistance>=1000000){
        totalResistance=totalResistance/1000000.0;
        printf("Resistance: %.2lf MOhms +/- %.2lf%%\n",totalResistance,tolerance);
    } else if (totalResistance>=1000){
        totalResistance=totalResistance/1000.0;
        printf("Resistance: %.2lf KOhms +/- %.2lf%%\n",totalResistance,tolerance);
    } else { // (totalResistance<1000){
        printf("Resistance: %.2lf Ohms +/- %.2lf%%\n",totalResistance,tolerance);
    }
    
	return 0;//return void
}//end of lab2
