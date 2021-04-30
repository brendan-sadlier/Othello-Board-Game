/*
 * Filename: display.h
 * Created on Fri Apr 30 2021 @ 18:48:54
 * Author: Brendan Sadlier
 * Description: Header file containing all output functions
 * Copyright (c) - 2021 Brendan Sadlier
 * All Rights Reserved
 */
#include <stdio.h>
#include <stdlib.h>

#include "color.h"

// Global Variables Created In display.h
char playerName[PLAYERS][MAX_STR_LEN]; //String Array to Store Player Names

// Global Variables Created In logic.h
extern char board[ROWS][COLUMNS];
extern int score[PLAYERS];
extern int currentPlayer;
extern int illegalMove;

// Opening Message at Program Start
void openingMessage () {

    printf(COLOR_GREEN_BOLD);
    printf("+---------------------------------+\n");
    printf("|             OTHELLO             |\n");
    printf("+---------------------------------+\n");
    printf(COLOR_RESET);

    printf(COLOR_BLUE_BOLD);
    printf("\n<------- ENTER PLAYER NAME ------->\n");
    printf(COLOR_RESET);

    printf(COLOR_CYAN_BOLD "PLAYER 1 > " COLOR_RESET);
    scanf(" %s", playerName[BLACK]);

    printf(COLOR_CYAN_BOLD "PLAYER 2 > " COLOR_RESET);
    scanf(" %s", playerName[WHITE]);

    printf("\n%s is BLACK (B)\n", playerName[BLACK]);
    printf("%s is WHITE (W)\n\n", playerName[WHITE]);
}

// Function to Display Current Score of Game
void scoreBoard () {

    printf(COLOR_BLUE_BOLD);
    printf("\n  <--- %-7s %2d : %-2d %s --->\n", playerName[BLACK], score[BLACK], score[WHITE], playerName[WHITE]);
    printf(COLOR_RESET);
}

// Function to Print Game Board to Console
void drawBoard () {

    int i, j;

    scoreBoard();

    printf("  +---+---+---+---+---+---+---+---+\n");

    for (i = 0; i < ROWS; ++i) {

        printf("%d |", i + 1);

        for (j = 0; j < COLUMNS; ++j) {

            switch (board[i][j]) {

                case BLACK:
                    printf(" %s ", BLACK_MARKER);
                    break;
                case WHITE:
                    printf(" %s ", WHITE_MARKER);
                    break;
                case PLAYABLE:
                    printf(" %s ", PLAYABLE_MARKER);
                    break;
                default:
                    printf(" %s ", EMPTY_MARKER);
                    break;
            }

            printf("|");
        }

        printf("\n  +---+---+---+---+---+---+---+---+\n");
    }

    printf("    A   B   C   D   E   F   G   H\n\n");
}

// Function to Output Message if Inputted Move is Illegal
void illegalMoveMessage () {

    if (illegalMove) {

        printf(COLOR_RED "Illgal Move! Please Try Again...\n" COLOR_RESET);
    }
}

// Function To Display Which Player's Turn It Is
void displayCurrentPlayer () {

    printf(COLOR_YELLOW_BOLD);
    printf("Current Player: ");

    if (currentPlayer == BLACK) {
        printf("%s\n", playerName[BLACK]);
    }

    else {
        printf("%s\n", playerName[WHITE]);
    }

    printf("===================================\n");
    printf(COLOR_RESET);
}

// Function to Output Message with Final Score and Winner at End Game
void winnerMessage () {

    printf(COLOR_GREEN_BOLD "!---------- FINAL SCORE ----------!\n" COLOR_RESET);

    printf("%s %2d : %2d %s\n\n", playerName[BLACK], score[BLACK], score[WHITE], playerName[WHITE]);

    if (score[WHITE] < score[BLACK]) {
        printf(COLOR_YELLOW_BOLD "%s WINS!\n" COLOR_RESET, playerName[BLACK]);
    }

    else if (score[BLACK] < score[WHITE]) {
        printf(COLOR_YELLOW_BOLD "%s WINS!\n" COLOR_RESET, playerName[WHITE]);
    }

    else {

        printf(COLOR_YELLOW_BOLD "DRAW GAME...\n" COLOR_RESET);
    }
}