# Number-Riddle-Game
A small number riddle solving game made in C.

Implementation

The game works within a loop which is started when the user starts a new game. The game loop populates the board using a 2d array with dimensions given by the user. As the user enters a number a function checks if the move is valid by calculating if that number is adjacent to the empty spot on the board. The movement is made simply by replacing the number with empty spot and the empty spot with the number. To check the game winning condition, the array essentially just needs to be in ascending order which means the user has completed the puzzle.
