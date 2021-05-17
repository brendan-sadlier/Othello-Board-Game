# Othello-Board-Game
COMP10050: Assignment 2 - Othello Board Game in C

Game Logic
Game Board, Player Names & Scores are all handles in arrays

Functiuon to check if a move is valid
- Each Path is ran through a function to check if the position inputted is valid on the board
- Check if it occupied by the opponent
- Calculates the distance to the closest marker

Function to Take Sqaures
- If the move is legal then the function assigns the player integer value
  to all squares on the path
- A seperate function then converts the integer to output the player marker on the board
