//Andrew Lau
//March 13, 2018
//APS105 Lab 7 Part 1 Final!! for submission
//Reversi AI based on pieces flipped

#include <stdio.h>
#include <stdbool.h>

//forward declaration
int getBoardSize();
void initBoard(char board[][26], int n);
char getCompClr();
void printBoard(char board[][26],int n);
bool getMove(char board[][26], int n, char clr);
bool moveAvail(char board[][26], int n, char colour);
bool validPos(char board[][26],int n,int row,int col);
int testMove(char board[][26], int n, char colourIn, int row,int col);
bool executeMove(char board[][26], int n, char colourIn, int row,int col);
void findBestPos(char board[][26], int n, char colour);
bool checkLegalInDirection(char board[][26], int n, int row,int col, char colour, int deltaRow, int deltaCol);
int flipPieces(char board[][26],int row,int col,char colour,int r,int c,bool execMove);
void dispNoMoveAvail(char colour);
void findWinner(char board[][26],int n);
void dispWinner(char colour);

/* main function
 * -runs initialization methods
 *      -calls for board dimension
 *      -calls to initilize board with U,W,B
 *      -asks user for colour computer will play
 *      -prints board layout
 * -black <B> plays first
 *      -if computer plays W, then ask user to input first move
 *      -if computer plays B, computer will make first move
 * -alternate between computer and user if moves exist
 * -when both have no moves possible, board is full, game over
 * -find player with most pieces and display this
 * 
 * List of Variables
 * boardDim - dimension of the board <nxn>
 * gameOver - true when mistake made by user
 * moveNotMade1 - true when move not made by computer
 * moveNotMade2 - true when move not made by user
 * board[][] - 2D array containing board layout
 * compClr - the colour computer plays
 * userClr - the colour user plays
 */
int main(void){
    int boardDim;
    bool gameOver=false,moveNotMade1,moveNotMade2;
    char board[26][26];
    char compClr,userClr='W';

    //game setup
    boardDim=getBoardSize();
    initBoard(board,boardDim);
    compClr=getCompClr();
    printBoard(board,boardDim);
    
    //game play

    //if computer plays W, user makes first move
    if (compClr=='W'){
        userClr='B';
        if(getMove(board,boardDim,userClr)==false){
            gameOver=true;
            dispWinner(compClr);
        }
    }
    
    //repeat below until board filled
    while(gameOver==false){
        moveNotMade1=false;
        moveNotMade2=false;
        
        //computer makes move if possible
        if(moveAvail(board,boardDim,compClr)==true){
            findBestPos(board,boardDim,compClr);
        } else {
            if(moveAvail(board,boardDim,userClr)==true){
                dispNoMoveAvail(compClr);
            }
            moveNotMade1=true;
        }
        
        //user makes move if possible
        if(moveAvail(board,boardDim,userClr)==true){
            if(getMove(board,boardDim,userClr)==false){
                gameOver=true;
                dispWinner(compClr);
                break;
            }
        } else {
            if(moveAvail(board,boardDim,compClr)==true){
                dispNoMoveAvail(userClr);
            }
            moveNotMade2=true;
        }
        
        // if no moves available for both players,
        // board is full, game is over
        if(moveNotMade1 && moveNotMade2){
            findWinner(board,boardDim);
            break;
        }
    }
	return 0;
} //end main function

/* getBoardSize function
 * -prompts and returns the size of the board
 */
int getBoardSize(){
    int n;
    printf("Enter the board dimension: ");
    scanf("%d",&n);
    return n;
} //end getBoardSize

/* initBoard function
 * -fills board array within board dimensions (n)
 * -middle topleft and bottomright are W
 * -middle topright and bottomleft are B
 * -all others are U
 */
void initBoard(char board[][26], int n){
    for (int r=0;r<n;r++){
        for (int c=0;c<n;c++){
            if (r==(n/2-1) && c==(n/2-1)){
                board[r][c]='W';
            } else if (r==(n/2) && c==(n/2)){
                board[r][c]='W';
            } else if (r==(n/2-1) && c==(n/2)){
                board[r][c]='B';
            } else if (r==(n/2) && c==(n/2-1)){
                board[r][c]='B';
            } else {
                board[r][c]='U';
            }
        }
    }
} //end initBoard

/* getCompClr function
 * -prompts and returns colour computer will play
 */
char getCompClr(){
    char clr;
    printf("Computer plays (B/W) : ");
    scanf(" %c",&clr);
    return clr;
} //end getCompClr

/* printBoard function
 * -first prints header with letters for columns
 * -nested for loop to run through all spaces
 * -print row letter when starting new row 
 */
void printBoard(char board[][26],int n){
    printf("  ");
    for (int c=0;c<n;c++){
        printf("%c",c+97);
    }
    printf("\n");
    for (int r=0;r<n;r++){
        for (int c=0;c<n;c++){
            if (c==0){
                printf("%c ",r+97);
            }
            printf("%c",board[r][c]);
        }
        printf("\n");
    }
} //end printBoard

/* getMove function
 * -prompts user for move
 * -accepts row and column letter
 * -if move is valid, print updated board, return true
 * -if move not valid, print error, return false
 */
bool getMove(char board[][26], int n, char clr){
    char rowIn,colIn;
    int row,col;
    
    printf("Enter move for colour %c (RowCol): ",clr);
    scanf(" %c%c",&rowIn,&colIn);
    
    row=(int)rowIn - 97;
    col=(int)colIn - 97;

    if(executeMove(board,n,clr,row,col)){
        printBoard(board,n);
        return true;
    }
    printf("Invalid move.\n");
    return false;
} //end getMove 

/* moveAvail function
 * -tests all spaces within board dimensions
 * -if at least one move possible, return true
 * -if no moves possible, return false
 */
bool moveAvail(char board[][26], int n, char colour){
    for(int i=0; i<n;i++){
        for(int j=0; j<n;j++){
            if(testMove(board,n,colour,i,j)>0){
                return true;
            }
        }
    }
    return false;
} //end moveAvail

/* validPos function
 * -tests if position is taken
 * -determines if position is within dimension
 * -if both true, return true
 * -if either not true, return false
 */
bool validPos(char board[][26],int n,int row,int col){
    
    if(board[row][col]=='U'){
        if (row>=0 && row<n && col>=0 && col<n){
            return true;
        }
    }
    return false;
} //end validPos

/* testMove function
 * -tests if position accepted is valid
 * -checks all 8 directions for flippable pieces
 * -if move possible in direction, get total number of pieces flippable
 * -return score found
 */
int testMove(char board[][26], int n, char colourIn, int row,int col){
    int score=0;
    
    if (validPos(board,n,row,col)){
        for (int r=-1;r<=1;r++){
            for(int c=-1;c<=1;c++){
                if(r==0 && c==0){
                    continue;
                }
                if(checkLegalInDirection(board, n, row, col, colourIn, r, c)==true){
                    score=score+flipPieces(board,row,col,colourIn,r,c,false);
                }
            }
        }
    }
    return score;
} //end testMove

/* executeMove function
 * -checks if position accepted is valid
 * -runs through all 8 directions
 * -if move possible in direction, flip pieces along that line
 *      -change position accepted to colour
 *      -make moveMade true, meaning move is valid
 * return moveMade, true if pieces flipped, false if no pieces flipped
 */
bool executeMove(char board[][26], int n, char colourIn, int row,int col){
    bool moveMade=false;
    
    if (validPos(board,n,row,col)){
        for (int r=-1;r<=1;r++){
            for(int c=-1;c<=1;c++){
                if(checkLegalInDirection(board, n, row, col, colourIn, r, c)){
                    flipPieces(board,row,col,colourIn,r,c,true);
                    board[row][col]=colourIn;
                    moveMade=true;
                }
            }
        }
    }
    return moveMade;
} //end executeMove function

/* findBestPos function
 * -finds best position to move for computer
 * -tests all spaces within board dimensions
 * -gets score for all spaces
 * -executes move on space with highest score
 * -prints move made for user
 * -print updated board
 */
void findBestPos(char board[][26], int n, char colour){
    int maxScore=0,tempScore;
    char bestRow,bestCol;

    for(int i=0; i<n;i++){
        for(int j=0; j<n;j++){
            tempScore=testMove(board,n,colour,i,j);
            if(tempScore>maxScore){
                maxScore=tempScore;
                bestRow=i;
                bestCol=j;
            }
            
        }
    }
    printf("Computer places %c at %c%c.\n",colour,bestRow+'a',bestCol+'a');
    executeMove(board, n, colour, bestRow, bestCol);
    printBoard(board,n);
} //end findBestPos

/* checkLegalInDirection function
 * -checks if pieces will be flipped in direction accepted
 * -determines if first piece in said direction is opposite colour
 * -determines if there exists a piece within dimension of said colour
 * -if line doesnt have same colour, or if unclaimed position found, return false
 * -false means not legal in direction
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){    
    //change to next space in direction
    row=row+deltaRow;
    col=col+deltaCol;
    
    if(row>=0 && row<n && col>=0 && col<n){ //use valid positions
        if (board[row][col]==colour || board[row][col]=='U'){ //opp colour in adjacent space
            return false;
        }
    }
    
    while(row>=0 && row<n && col>=0 && col<n){ //use valid positions
        
        //repeat until empty spot or same colour found
        if (board[row][col]=='U'){ //only one colour on line
            return false;
        } else if (board[row][col]==colour){ //both colours on line
            return true;
        }
        
        row=row+deltaRow; //change row by -1/0/+1
        col=col+deltaCol; //change col by -1/0/+1
    }
    
    return false;
} //end checkLegalInDirection

/* flipPieces function
 * -flips pieces along direction accepted if instructed
 * -tallies number of pieces flippable
 * -repeats until same colour found
 * -return number of pieces flipped
 */
int flipPieces(char board[][26],int row,int col,char colour,int r,int c,bool execMove){
    int score=0;
    int deltaR,deltaC;
    
    deltaR=r;
    deltaC=c;
    
    while(board[row+r][col+c]!=colour){
        if(execMove){
            board[row+r][col+c]=colour;
        }
        
        score=score+1;
        r=r+deltaR;
        c=c+deltaC;
    }
    
    return score;
} //end flipPieces

/* dispNoMoveAvail function
 * -prints message for user if no move available for said colour
 */
void dispNoMoveAvail(char colour){
    printf("%c player has no valid move.\n",colour);
} //end dispNoMoveAvail

/* findWinner function
 * -runs through board within dimensions
 * -counts number of each players pieces
 * -displays winners colour if not a draw
 */
void findWinner(char board[][26],int n){
    int wScore=0,bScore=0;
    
    //tally total number of pieces for both players
    for(int i=0; i<n;i++){
        for(int j=0; j<n;j++){
            if(board[i][j]=='W'){
                wScore=wScore+1;
            } else if(board[i][j]=='B'){
                bScore=bScore+1;
            }
        }
    }
    
    //display results
    if(wScore>bScore){
        dispWinner('W');
    } else if (wScore<bScore){
        dispWinner('B');
    } else {//wScore==bScore
        printf("Draw!\n");
    }
} //end findWinner

/* dispWinner function
 * -displays the winning colour in correct format
 */ 
void dispWinner(char colour){
    printf("%c player wins.\n",colour);
} //end dispWinner