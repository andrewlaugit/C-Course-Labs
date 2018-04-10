#include <stdio.h>
#include <stdbool.h>

//forward declaration
int getBoardSize();
void initBoard(char board[][26], int n);
void printBoard(char board[][26],int n);
void getBoardConfig(char board[][26], int n);
void getMove(char board[][26], int n);
void testMove(char board[][26],int n, char colourIn,char rowIn,char colIn, bool execMove);
bool positionInBounds(int n,char row,char col);
void findAvailMoves(char board[][26],int n,char colour);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
void flipPieces(char board[][26],char row,char col,char colour,int r,int c);

/* main function
 * - calls other functions to run setup of game
 * - creates board array containing board setup
 * 
 * List of Variables
 * boardDim - dimension of the board 
 * board[][] - array containing board layout
 */
int main(void){
    int boardDim;
    char board[26][26];
    boardDim=getBoardSize();
    initBoard(board,boardDim);
    printBoard(board,boardDim);
    getBoardConfig(board,boardDim);
    printBoard(board,boardDim);
    findAvailMoves(board,boardDim, 'W');
    findAvailMoves(board,boardDim, 'B');
    getMove(board,boardDim);
	return 0;
} //end main function

/* getBoardSize function
 * - prompts and accepts board dimension
 */
int getBoardSize(){
    int n;
    printf("Enter the board dimension: ");
    scanf("%d",&n);
    return n;
}

/* initBoard function
 * - initializes board layout
 * - center W and B pieces are placed
 * - all other spaces filled with U
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
}

/* printBoard function
 * - runs through array and prints within dimension
 * - prints row and column labels
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
}

/* getBoardConfig function
 * - accepts initial baord config
 * - modifies board according to input
 * 
 * List of Variables
 * colourIn - first char entered, colour
 * rowIn - second char entered, row
 * colIn - third char entered, column
 */
void getBoardConfig(char board[][26], int n){
    char colourIn,rowIn,colIn;
    printf("Enter board configuration:\n");
    do{
        scanf(" %c%c%c",&colourIn,&rowIn,&colIn);
        if (colourIn=='!' && rowIn =='!' && colIn=='!'){
            break;
        }
        board[rowIn-97][colIn-97]=colourIn;
    }while(colourIn!='!' && rowIn!='!' && colIn!='!');
} //end getBoardConfig

/* getMove function
 * - prompts and accepts user move
 * - calls testMove function to make move if valid
 */
void getMove(char board[][26], int n){
    char colourIn,rowIn,colIn;
    printf("Enter a move:\n");
    scanf(" %c%c%c",&colourIn,&rowIn,&colIn);
    testMove(board,n,colourIn,rowIn,colIn,true);
} //end getMove function

/* testMove function
 * - sends commands to checkLegalInDirection function
 * - sends all direction combinations to function
 * - calls flipPieces function to execute move if wanted
 * 
 * List of Variables
 * execMove - determines whether move should be carried out
 * moveValid - determines whether move is valid
 */
void testMove(char board[][26], int n, char colourIn, char rowIn, char colIn, bool execMove){
    bool moveValid=false;
    if (positionInBounds(n,rowIn-'a',colIn-'a')){
        for (int r=-1;r<=1;r++){
            for(int c=-1;c<=1;c++){
                if(checkLegalInDirection(board, n, rowIn, colIn, colourIn, r, c)){
                    moveValid=true;
                    if(execMove){
                        flipPieces(board,rowIn,colIn,colourIn,r,c);
                    }
                }
            }
        }
    }
    if (moveValid && execMove){
        board[rowIn-97][colIn-97]=colourIn;
        printf("Valid move.\n");
        printBoard(board,n);
    } else if(moveValid && !execMove) {
        printf("%c%c\n",rowIn,colIn);
    } else if (!moveValid && execMove){
        printf("Invalid move.\n");
        printBoard(board,n);
    }
} //end testMove function

/* findAvailMoves function
 * - runs through all positions on board within dimensions
 * - calls testMove for all positions on board
 */
void findAvailMoves(char board[][26], int n, char colour){
    printf("Available moves for %c:\n",colour);
    for(int i=97; i<n+97;i++){
        for(int j=97; j<=n+97;j++){
            testMove(board,n,colour,i,j,false);
        }
    }
}

/* positionInBounds function
 * - determines if move is within the dimensions of board
 */
bool positionInBounds(int n,char row,char col){
    if (row>=0 && row<n && col>=0 && col<n){
        return true;
    }
    return false;
}

/* checkLegalInDirection function
 * - determines if move is legal in direction specified
 * - checks if piece of same colour exists in direction
 * - checks if piece beside position is of opposite colour
 */
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){
    int rowIndex=row-97,colIndex=col-97;
    
    if (board[rowIndex][colIndex]=='U'){ //space is not taken
    
        //change to next space in direction
        rowIndex=rowIndex+deltaRow;
        colIndex=colIndex+deltaCol;
        
        if(positionInBounds(n,rowIndex,colIndex)){
            if (board[rowIndex][colIndex]!='U' && board[rowIndex][colIndex]!=colour ){ //opp colour         
                //repeat while within board bounds
                while(positionInBounds(n,rowIndex,colIndex)){
                    if (board[rowIndex][colIndex]=='U'){ //only one colour on line
                        return false;
                    } else if (board[rowIndex][colIndex]==colour){ //both colours on line
                        return true;
                    }                    
                    rowIndex=rowIndex+deltaRow; //change row by -1/0/+1
                    colIndex=colIndex+deltaCol; //change col by -1/0/+1
                }
            }
        }
    }
    return false;
}

/* flipPieces function
 * - flips pieces along a direction
 * - runs until piece of same colour found
 */
void flipPieces(char board[][26],char row,char col,char colour,int r,int c){
    int deltaR,deltaC;
    
    deltaR=r;
    deltaC=c;
    
    while(board[row-97+r][col-97+c]!=colour){
        board[row-97+r][col-97+c]=colour;
        r=r+deltaR;
        c=c+deltaC;
    } 
} //end flipPieces