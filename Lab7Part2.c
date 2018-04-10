// Andrew Lau
// March 13, 2018
// APS105 Lab 7 Part 2 Final!! for submission
// Reversi AI based on algorithm created

#include <stdio.h>
#include <stdbool.h>
#include "lab7part2lib.h"

// forward declaration
int getBoardSize();
void initBoard(char board[][26], int n);
char getCompClr();
void printBoard(char board[][26], int n);
bool getMove(char board[][26], int n, char clr);
bool moveAvail(char board[][26], int n, char colour);
bool validPos(char board[][26], int n, int row, int col);
int scoreMove(char board[][26], int n, char clr, int row, int col);
bool executeMove(char board[][26], int n, char colourIn, int row, int col);
void findBestPos(char board[][26], int n, char compClr, char userClr);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
int flipPieces(char board[][26], int n,int row, int col, char colour, int r, int c, bool execMove);
void dispNoMoveAvail(char colour);
void findWinner(char board[][26], int n);
void dispWinner(char colour);
void checkCornerEmpty(char board[][26], int n, int row, int col, bool* cornerEmpty);

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
    bool gameOver = false, moveNotMade1, moveNotMade2;
    char board[26][26];
    char compClr, userClr = 'W';

    //******************* game setup ******************************//
    boardDim = getBoardSize();
    initBoard(board, boardDim);
    compClr = getCompClr();
    printBoard(board, boardDim);

    //******************* game play ******************************//
    // if computer plays W, user makes first move
    if (compClr == 'W') {
        userClr = 'B';
        if (getMove(board, boardDim, userClr) == false) {
            gameOver = true;
            dispWinner(compClr);
        }
    }

    // repeat below until board filled
    while (gameOver == false) {
        moveNotMade1 = false;
        moveNotMade2 = false;

        // computer makes move if possible
        if (moveAvail(board, boardDim, compClr)) {
            findBestPos(board, boardDim, compClr, userClr);
        } else {
            if (moveAvail(board, boardDim, userClr)) {
                dispNoMoveAvail(compClr);
            }
            moveNotMade1 = true;
        }

        // user makes move if possible
        if (moveAvail(board, boardDim, userClr)) {
            if (!getMove(board, boardDim, userClr)) {
                gameOver = true;
                dispWinner(compClr);
                break;
            }
        } else {
            if (moveAvail(board, boardDim, compClr)) {
                dispNoMoveAvail(userClr);
            }
            moveNotMade2 = true;
        }

        // if no moves available for both players, game is over
        if (moveNotMade1 && moveNotMade2) {
            findWinner(board, boardDim);
            break;
        }
    }
    return 0;
} // end main function

/* getBoardSize function
 * -prompts and returns the size of the board
 */
int getBoardSize(){
    int n;
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    return n;
} // end getBoardSize

/* initBoard function
 * -fills board array within board dimensions (n)
 * -middle topleft and bottomright are W
 * -middle topright and bottomleft are B
 * -all others are U
 */
void initBoard(char board[][26], int n){
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r == (n / 2 - 1) && c == (n / 2 - 1)) {
                board[r][c] = 'W';
            } else if (r == (n / 2) && c == (n / 2)) {
                board[r][c] = 'W';
            } else if (r == (n / 2 - 1) && c == (n / 2)) {
                board[r][c] = 'B';
            } else if (r == (n / 2) && c == (n / 2 - 1)) {
                board[r][c] = 'B';
            } else {
                board[r][c] = 'U';
            }
        }
    }
} // end initBoard

/* getCompClr function
 * -prompts and returns colour computer will play
 */
char getCompClr(){
    char clr;
    printf("Computer plays (B/W) : ");
    scanf(" %c", &clr);
    return clr;
} // end getCompClr

/* printBoard function
 * -first prints header with letters for columns
 * -nested for loop to run through all spaces
 * -print row letter when starting new row
 */
void printBoard(char board[][26], int n){
    printf("  ");
    for (int c = 0; c < n; c++) {
        printf("%c", c + 97);
    }
    printf("\n");
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (c == 0) {
                printf("%c ", r + 97);
            }
            printf("%c", board[r][c]);
        }
        printf("\n");
    }
} // end printBoard

/* getMove function
 * -prompts user for move
 * -accepts row and column letter
 * -if move is valid, print updated board, return true
 * -if move not valid, print error, return false
 */
bool getMove(char board[][26], int n, char clr){
    int rowAI,colAI;
    /*
    findSmarterMove(board, n, clr, &rowAI, &colAI);
    printf("Testing AI move (row,col): %d %d\n", rowAI + 97, colAI + 97);
    //*/

    ///*
    char rowIn,colIn;
    printf("Enter move for colour %c (RowCol): ",clr);
    scanf(" %c%c",&rowIn,&colIn);
    rowAI=rowIn-97;
    colAI=colIn-97;
    // */

    if (executeMove(board, n, clr, rowAI, colAI)) {
        printBoard(board, n);
        return true;
    }
    printf("Invalid move.\n");
    return false;
} // end getMove

/* moveAvail function
 * -tests all spaces within board dimensions
 * -if at least one move possible, return true
 * -if no moves possible, return false
 */
bool moveAvail(char board[][26], int n, char colour){
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (validPos(board, n, row, col)) {
                for (int r = -1; r <= 1; r++) {
                    for (int c = -1; c <= 1; c++) {
                        if (r == 0 && c == 0) {
                            continue;
                        }
                        if (checkLegalInDirection(board, n, row, col, colour, r, c)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
} // end moveAvail

/* validPos function
 * -tests if position is taken
 * -determines if position is within dimension
 * -if both true, return true
 * -if either not true, return false
 */
bool validPos(char board[][26], int n, int row, int col){
    if (row >= 0 && row < n && col >= 0 && col < n) {
        if (board[row][col] == 'U') {
            return true;
        }
    }
    return false;
} // end validPos

/* scoreMove function
 * - accepts a row and column position to score
 * - makes sure spot is empty, and move is valid
 * - checks all directions for potential number of pieces flipped
 * - gives each strategic position on board a unique score
 * 
 * Scoring Theory
 * - corners = 500
 * - 3 spaces around corner = -250
 * - spaces 2 away and aligned with corner = 40
 * - spaces along the edges = 5
 */
int scoreMove(char board[][26], int n, char clr, int row, int col){
    const int CORNER = 500, BAD = -250, ALIGN = 40, EDGE=5;
    int score = 0, rowCheck, colCheck;
    bool cornerEmpty = false;

    if (validPos(board, n, row, col)) { // space is empty
        for (int r = -1; r <= 1; r++) {
            for (int c = -1; c <= 1; c++) {
                if (r == 0 && c == 0) {
                    continue;
                }
                if (checkLegalInDirection(board, n, row, col, clr, r, c) == true) {
                    score = score + flipPieces(board, n, row, col, clr, r, c, false);

                    // corners get 500 points
                    if (row == 0 || row == (n - 1)) {
                        if (col == 0 || col == (n - 1)) {
                            score = score + CORNER;
                        }
                    }
                    
                    //determine position is next to corner
                    cornerEmpty = false;
                    for (int rChange = -1; rChange <= 1; rChange++) {
                        for (int cChange = -1; cChange <= 1; cChange++) {
                            rowCheck = row - rChange;
                            colCheck = col - cChange;
                            checkCornerEmpty(board, n, rowCheck, colCheck, &cornerEmpty); //-1,-1
                        }
                    }

                    // 3 spots around corners get -250 if corner is empty
                    // spots 2 places away and aligned with corner get 40 points
                    // spots on edge get 5 points
                    if (n > 4) {
                        if (cornerEmpty) {
                            if (row == 0 || row == (n - 1)) {
                                if (col == 1 || col == (n - 2)) {
                                    score = score + BAD;
                                } else if (col == 2 || col == (n - 3)) {
                                    score = score + ALIGN;
                                } else {
                                    score = score + EDGE;
                                }
                            } else if (row == 1 || row == (n - 2)) {
                                if (col == 0 || col == (n - 1) || col == 1 || col == (n - 2)) {
                                    score = score + BAD;
                                } 
                            } else if (row == 2 || row == (n - 3)) {
                                if (col == 0 || col == (n - 1)) {
                                    score = score + ALIGN;
                                } else if (col == 2 || col == (n - 3)) {
                                    score = score + ALIGN;
                                }
                            } else if (col==0 || col==(n-1)){
                                score = score + EDGE;
                            }
                        }
                    }
                }
            }
        }
    }
    return score;
} // end scoreMove

/* checkCornerEmpty function
 * - if row and col within dimension bounds
 * - if position is empty, set cornerEmpty = true
 */
void checkCornerEmpty(char board[][26], int n, int row, int col, bool* cornerEmpty){
    if (row == 0 || row == (n - 1)) {
        if (col == 0 || col == (n - 1)) {
            if (board[row][col] == 'U') {
                if (*cornerEmpty == false) {
                    *cornerEmpty = true;
                }
            }
        }
    }
}

/* executeMove function
 * -checks if position accepted is valid
 * -runs through all 8 directions
 * -if move possible in direction, flip pieces along that line
 *      -change position accepted to colour
 *      -make moveMade true, meaning move is valid
 * return moveMade, true if pieces flipped, false if no pieces flipped
 */
bool executeMove(char board[][26], int n, char colourIn, int row, int col){
    bool moveMade = false;

    if (validPos(board, n, row, col)) {
        for (int r = -1; r <= 1; r++) {
            for (int c = -1; c <= 1; c++) {
                if (checkLegalInDirection(board, n, row, col, colourIn, r, c)) {
                    flipPieces(board, n,row, col, colourIn, r, c, true);
                    board[row][col] = colourIn;
                    moveMade = true;
                }
            }
        }
    }
    return moveMade;
} // end executeMove function

/* findBestPos function
 * -finds highest scoring position within board
 * -executes move on space with highest score
 * -prints move made for user
 * -print updated board
 * 
 * Logic Description
 * -run through all spaces possible within board
 * -make of copy of board
 * -get the score of the position
 * -make move on the copy
 * -subtract score with total score possible for the opponent
 * -change the best row and col if score highest
 */
void findBestPos(char board[][26], int n, char compClr, char userClr) {
    int maxScore = -9999, tempScore, oppTotal = 0;
    int bestRow, bestCol;
    char boardCopy[26][26];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            
            //make a copy of the board
            for (int ii = 0; ii < 26; ii++) {
                for (int jj = 0; jj < 26; jj++) {
                    boardCopy[ii][jj] = board[ii][jj];
                }
            }
            
            //make move on copy of board if valid
            tempScore = scoreMove(board, n, compClr, i, j);
            if (tempScore == 0) {
                continue;
            }
            executeMove(boardCopy, n, compClr, i, j);
            
            // find total of all scores for oponent
            oppTotal = 0;
            for (int r1 = 0; r1 < n; r1++) {
                for (int c1 = 0; c1 < n; c1++) {
                    oppTotal = oppTotal + scoreMove(boardCopy, n, userClr, r1, c1);
                }
            }
            
            tempScore = tempScore - oppTotal;
            if (tempScore > maxScore) {
                maxScore = tempScore;
                bestRow = i;
                bestCol = j;
            } else if (tempScore == maxScore) {
                if (i == 0 || i == (n - 1)) {
                    if (j == 0 || j == (n - 1)) {
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
        }
    }
    executeMove(board, n, compClr, bestRow, bestCol);
    printf("Computer places %c at %c%c.\n", compClr, bestRow + 'a', bestCol + 'a');

    printBoard(board, n);
} // end findBestPos

/* checkLegalInDirection function
 * -checks if pieces will be flipped in direction accepted
 * -determines if first piece in said direction is opposite colour
 * -determines if there exists a piece within dimension of said colour
 * -if line doesnt have same colour, or if unclaimed position found, return false
 * -false means not legal in direction
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){

    // change to next space in direction
    row = row + deltaRow;
    col = col + deltaCol;

    if (row >= 0 && row < n && col >= 0 && col < n) { // use valid positions
        if (board[row][col] == colour || board[row][col] == 'U') { // opp colour in adjacent space
            return false;
        }
    }

    while (row >= 0 && row < n && col >= 0 && col < n) { // use valid positions

        // repeat until empty spot or same colour found
        if (board[row][col] == 'U') { // only one colour on line
            return false;
        } else if (board[row][col] == colour) { // both colours on line
            return true;
        }
        
        row = row + deltaRow; // change row by -1/0/+1
        col = col + deltaCol; // change col by -1/0/+1
    }
    return false;
} // end checkLegalInDirection

/* flipPieces function
 * -flips pieces along direction accepted if instructed
 * -tallies number of pieces flippable
 * -repeats until same colour found
 * -return number of pieces flipped + bonus
 */
int flipPieces(char board[][26], int n, int row, int col, char colour, int r, int c, bool execMove){
    int score = 0;
    int deltaR, deltaC;

    deltaR = r;
    deltaC = c;

    while (board[row + r][col + c] != colour) {
        if (execMove) {
            board[row + r][col + c] = colour;
        }
        
        //bonus points for flipping pieces on 2 diagonals
        if ((row + r) - (col + r) ==0 || (row + r)+(col + r) == n){
            score = score + 10;
        }

        score = score + 1;
        r = r + deltaR;
        c = c + deltaC;
    }

    return score;
} // end flipPiece

/* dispNoMoveAvail function
 * -prints message for user if no move available for said colour
 */
void dispNoMoveAvail(char colour){
    printf("%c player has no valid move.\n", colour);
} // end dispNoMoveAvail

/* findWinner function
 * -runs through board within dimensions
 * -counts number of each players pieces
 * -displays winners colour if not a draw
 */
void findWinner(char board[][26], int n){
    int wScore = 0, bScore = 0;

    // tally total number of pieces for both players
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'W') {
                wScore = wScore + 1;
            } else if(board[i][j]=='B'){
                bScore = bScore + 1;
            }
        }
    }

    // display results
    if (wScore > bScore) {
        dispWinner('W');
    } else if (wScore < bScore) {
        dispWinner('B');
    } else { // wScore==bScore
        printf("Draw!\n");
    }
} // end findWinner

/* dispWinner function
 * -displays the winning colour in correct format
 */
void dispWinner(char colour){
    printf("%c player wins.\n", colour);
} // end dispWinner