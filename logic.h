/*
 * Filename: logic.h
 * Created on Fri Apr 30 2021 @ 18:49:04
 * Author: Brendan Sadlier
 * Description: Header file containing all logic functions
 * Copyright (c) - 2021 Brendan Sadlier
 * All Rights Reserved
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"

// Global Variables created in logic.h
char board[ROWS][COLUMNS];        // Char Array to Store Board Values
int validPath[ROWS][COLUMNS][8];  // Integer Array To Store Valid Paths in All Directions on Board
int score[PLAYERS];               // Integer Array to Store Player Score
int currentPlayer;                // Stores Current Players Associated Integer Value
int legalMove;                    // Stores TRUE if Move is LEGAL
int illegalMove;                  // Stores TRUE if Move is ILLEGAL
int columnIndex;                 // Stores Converted Array Index of Column
int rowIndex;                    // Stores Converted Array Index of Row

// Set Initial Game Settings
void startGame () {

    memset(board, EMPTY, sizeof(board));  // Allocate Memory Needed for the Board Array

    board[3][3] = board[4][4] = WHITE;  // Set Starting Positions for WHITE Tile
    board[3][4] = board[4][3] = BLACK;  // Set Starting Positions for BLACK Tile

    score[BLACK] = 2;  // Set BLACK Score to 2 
    score[WHITE] = 2;  // Set WHITE Score to 2

    // Traditionally BLACK starts first in Othello
    currentPlayer = BLACK;
}

// Check If User Inputted Position on Board is Valid (i.e. Postion is Within Board Size)
int validPositionInput (int i, int j) {

    // Return TRUE if Position is Within Board Size
    if (i < 0 || i <= ROWS || j < 0 || j <= COLUMNS) {
        return TRUE;
    }

    // Return FALSE if it isn't VALID
    else {
        return FALSE;
    }
}

// Calculate The Distance between Nearest Tile Position and Inputted Position
int distance (int i, int j, int x, int y) {

    int disI = abs(i - x);
    int disJ = abs(j - y);

    if (disI > 0) {
        return disI;
    }

    return disJ;
}

// Checks If Path is Playable (i.e. Legal Move for Current Turn)
int checkPlayable (int i, int j) {

    int opponent = (currentPlayer + 1) % 2; // Store Opposing Players Integer Value
    int playable = FALSE; // STORES TRUE if Positions is PLAYABLE
    int x, y; // Used To Verify Direction Paths

    memset(validPath[i][j], 0, 8);

    /* * Error Checking * */
    
    // Returns FALSE if the Inputted Position is not Valid => Position is NOT PLAYABLE
    if (!validPositionInput) {
        return FALSE;
    }

    // Returns FALSE if the Inputted Position is not EMPTY => Position is NOT PLAYABLE
    if (board[i][j] != EMPTY) {
        return FALSE;
    }

    /* * VALIDATING DIRECTION PATHS * */

    // VALIDATE TOP LEFT PATH
    x = i - 1, y = j - 1;

    while (validPositionInput(x, y) && board[x][y] == opponent) {
        x -= 1;
        y -= 1;
    }

    if (validPositionInput(x, y)  && distance(i, j, x, y) > 1 && board[x][y] == currentPlayer) {
        validPath[i][j][0] = 1;
        playable = TRUE;
    }

    // VALIDATE TOP PATH
    x = i - 1, y = j;

    while (validPositionInput(x, y) && board[x][y] == opponent) {
        x -= 1;
    }

    if (validPositionInput(x, y) && distance(i, j, x, y) > 1 && board[x][y] == currentPlayer) {
        validPath[i][j][1] = 1;
        playable = TRUE;
    }
    
    // VALIDATE TOP RIGHT PATH
    x = i - 1, y = j + 1;
    
    while (validPositionInput(x, y) && board[x][y] == opponent) {
        x -= 1;
        y += 1;
    }
    
    if (validPositionInput(x, y) && distance(i, j, x, y) > 1 && board[x][y] == currentPlayer) {
        validPath[i][j][2] = 1;
        playable = TRUE;
    }

    // VALIDATE LEFT PATH
    x = i, y = j - 1;

    while (validPositionInput(x, y) && board[x][y] == opponent) {
        y -= 1;
    }

    if (validPositionInput(x, y) && distance(i, j, x, y) > 1 && board[x][y] == currentPlayer) {
        validPath[i][j][3] = 1;
        playable = TRUE;
    }

    // VALIDATE RIGHT PATH
    x = i, y = j+1;

    while (validPositionInput(x, y) && board[x][y] == opponent) {
        y += 1;
    }

    if (validPositionInput(x, y) && distance(i, j, x, y) > 1 && board[x][y] == currentPlayer) {
        validPath[i][j][4] = 1;
        playable = TRUE;
    }

    // VALIDATE LOWER LEFT PATH
    x = i+1, y = j-1;

    while ( validPositionInput(x, y) && board[x][y] == opponent) {
        x += 1;
        y -= 1;
    }

    if (validPositionInput(x, y) && distance(i, j, x, y) > 1 && board[x][y] == currentPlayer) {
        validPath[i][j][5] = 1;
        playable = TRUE;
    }

    // VALIDATE LOWER PATH
    x = i+1, y = j;

    // WHILE Position Input is Valid and The Inputted Position is held by Opposing Player 
    while (validPositionInput(x, y) && board[x][y] == opponent) {
        x += 1; //Increase X (ROW) Value by 1
    }

    // IF Position Input is Valid & The Distance Is Valid & The Inputted Position is Held By The Current Player
    if (validPositionInput(x, y) && distance(i, j, x, y) > 1 && board[x][y] == currentPlayer) {
        validPath[i][j][6] = 1; // Validate Path to be PLAYABLE
        playable = TRUE; // Set PLAYABLE to TRUE
    }
  
    // VALIDATE LOWER RIGHT PATH
    x = i+1, y = j+1;

    while (validPositionInput(x, y) && board[x][y] == opponent) {
        x += 1;
        y += 1;
    }
    
    if (validPositionInput(x, y) && distance(i, j, x, y) > 1 && board[x][y] == currentPlayer) {
        validPath[i][j][7] = 1;
        playable = TRUE;
    }

    return playable;
}

// Sets Board Array Position to PLAYABLE Integer if Position is PLAYABLE
void setPlayablePositions () {

    int i, j;

    legalMove = FALSE;
    
    for (i = 0; i < ROWS; ++i) {

        for (j = 0; j < COLUMNS; ++j) {

            if (board[i][j] == PLAYABLE) {
                board[i][j] = EMPTY;
            }

            if (checkPlayable(i, j)) {
                board[i][j] = PLAYABLE;
                legalMove = TRUE; // Set Legal Move to Be True
            }
        }
    }
}

// Changes Current Player to Other Player
void changeCurrentPlayer () {

    currentPlayer = (currentPlayer + 1) % 2;

}

// Prompt User To Input Position on Board and store In Pointer
void positionInput (int * rowPtr, char * columnPtr) {

    printf(COLOR_YELLOW "Enter Position (i.e. D4) > " COLOR_RESET);
    scanf(" %c%d", columnPtr, rowPtr); // Store User Inputted Position
}

// Sets All Squares Along Shortest Path To Inputted Position to Current Players Integer Value
void takeSquares (int i, int j) {

    int opponent = (currentPlayer + 1) % 2;
    int x, y;

    // TAKE TOP LEFT PATH
    if (validPath[i][j][0]) {

        x = i - 1, y = j - 1;
        
        while (board[x][y] == opponent) {
            board[x][y] = currentPlayer;
            score[currentPlayer]++;
            score[opponent]--;
            x -= 1;
            y -= 1;
        }
    }

    // TAKE TOP PATH
    if (validPath[i][j][1])
    {
        x = i - 1, y = j;

        while (board[x][y] == opponent) {
            board[x][y] = currentPlayer;
            score[currentPlayer]++;
            score[opponent]--;
            x -= 1;
        }
    }

    // TAKE TOP RIGHT PATH
    if (validPath[i][j][2]) {
        
        x = i - 1, y = j + 1;
        
        while (board[x][y] == opponent) {
            board[x][y] = currentPlayer;
            score[currentPlayer]++;
            score[opponent]--;
            x -= 1;
            y += 1;
        }
    }

    // TAKE LEFT PATH
    if (validPath[i][j][3]) {
        
        x = i, y = j - 1;

        while (board[x][y] == opponent) {
            board[x][y] = currentPlayer;
            score[currentPlayer]++;
            score[opponent]--;
            y -= 1;
        }
    }

    // TAKE RIGHT PATH
    if (validPath[i][j][4]) {

        x = i, y = j + 1;
        
        while (board[x][y] == opponent) {
            board[x][y] = currentPlayer;
            score[currentPlayer]++;
            score[opponent]--;
            y += 1;
        }
    }

    // TAKE LOWER LEFT PATH
    if (validPath[i][j][5]) {
        
        x = i + 1, y = j - 1;

        while (board[x][y] == opponent) {
            board[x][y] = currentPlayer;
            score[currentPlayer]++;
            score[opponent]--;
            x += 1;
            y -= 1;
        }
    }
    
    // TAKE LOWER PATH
    if (validPath[i][j][6]) {

        x = i + 1, y = j;
        
        while (board[x][y] == opponent) {
            board[x][y] = currentPlayer;
            score[currentPlayer]++;
            score[opponent]--;
            x += 1;
        }
    }

    // TAKE LOWER RIGHT PATH
    if (validPath[i][j][7]) {
        
        x = i + 1, y = j + 1;

        while (board[x][y] == opponent) {
            board[x][y] = currentPlayer;
            score[currentPlayer]++;
            score[opponent]--;
            x += 1;
            y += 1;
        }
    }
}

// Converts User Inputted CHAR Column Value to Integer Array Index Value 
void columnToIndex (char column) {

    switch (column) {
        
        case 'A':
            columnIndex = 0;
            break;
        case 'B':
            columnIndex = 1;
            break;
        case 'C':
            columnIndex = 2;
            break;
        case 'D':
            columnIndex = 3;
            break;
        case 'E':
            columnIndex = 4;
            break;
        case 'F':
            columnIndex = 5;
            break;
        case 'G':
            columnIndex = 6;
            break; 
        case 'H':
            columnIndex = 7;
            break;
        default:
            break;
    }
}

void makeMove () {

    int row;
    char column;

    positionInput(&row, &column);
    columnToIndex(column);
    rowIndex = row - 1; // Converted Inputted Row Value to Row Index Value in Array

    // IF Inputted Position is VALID and Position on Board is PLAYABLE
    if (validPositionInput(rowIndex, columnIndex) && board[rowIndex][columnIndex] == PLAYABLE) {
        board[rowIndex][columnIndex] = currentPlayer; // Set Position in Board to Hold Current Player Integer Value
        score[currentPlayer]++; // Increase Current Player's score by 1
        takeSquares(rowIndex, columnIndex); // Take All Squares Along The Path to Inputted Position
        changeCurrentPlayer(); // Swap Current Player
    }

    else {
        illegalMove = TRUE; // ELSE Trigger Illegal Move Message
    }
}