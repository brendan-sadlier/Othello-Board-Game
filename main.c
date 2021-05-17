/*
 * Filename: main.c
 * Created on Fri Apr 30 2021 @ 18:49:11
 * Author: Brendan Sadlier
 * Description: Main source file for Othello Board Game
 * Copyright (c) - 2021 Brendan Sadlier
 * All Rights Reserved
 */
#include <stdlib.h>
#include <stdio.h>

#include "macros.h"
#include "logic.h"
#include "display.h"

// Global Variables Created in main.c
int gameEnd = FALSE; // Returns TRUE if Game has Ended
int skipTurn = FALSE; // Returns TRUE if a Turn has been Skipped

// Global Variables Created in logic.h
extern int illegalMove;
extern int legalMove;

int main () {

    system("clear"); // Clears Console of All Previous Text

    openingMessage();
    startGame(); // Sets Initial Game Settings

    while (!gameEnd) {

        if (!illegalMove) {
            setPlayablePositions();
        }

        if (!legalMove) {
                
            if (skipTurn) { 
                gameEnd = 1;
                drawBoard();
                continue;
            }

            skipTurn = 1;
            changeCurrentPlayer();
            continue;
        }

        skipTurn = 0;
        drawBoard();
        displayCurrentPlayer();
        illegalMoveMessage();
        makeMove();
    }

    winnerMessage();
    writeScoreToFile();
}