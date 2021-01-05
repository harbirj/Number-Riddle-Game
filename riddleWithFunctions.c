//The following code is of Number Riddle game.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Show the board on the screen
void printTable(int rows, int cols, int array[rows][cols]);

// Randomly populate the array except the last element
void fillArray(int row, int col, int array[row][col]);

// Generate a random number between min and max, inclusive.
int MyRand(int min, int max);

// Check if an element exists in the first couple of elements of an array
int exists(int row, int col, int num, int array[row][col]);

int main() {

    puts("**************************");
    puts("******* Welcome to *******");
    puts("*** Number Riddle Game ***");
    puts("******** Ver. 2.0 ********");
    puts("******* Programmer *******");
    puts("****** Harbir Jaura ******");
    puts("");

    srand(time(NULL));

    do {

        // Variables for number of rows and columns
        int row, col;

        // Get the number of rows and columns from the user
        do {
            printf("Enter number of rows (3 - 8):\n");
            scanf("%d",&row);
        } while (row <3 || row > 8);

        do {
            printf("Enter number of columns (3 - 8):\n");
            scanf("%d",&col);
        } while (col < 3 || col > 8);

        // Create a two-dimensional array for the game board, and initialize the elements with zero
        int p[row][col];
        for(int i=0; i<row; i++)                      
        {
            for(int j=0;j<col;j++) 
            {
                p[i][j] = 0;
            }
        }

        // Generate random numbers and put in the board cells
        fillArray(row, col, p);

        // Randomize the location of the empty cell
        int emptyPositionRow = rand() % (row-1);
        int emptyPositionCol = rand() % (col-1);
        p[row-1][col-1] = p[emptyPositionRow][emptyPositionCol];
        p[emptyPositionRow][emptyPositionCol] = 0;

        puts("");

        // Show the board on the screen
        printTable(row, col, p);

        int won = 0;

        time_t start, end;      // Record the time taken in each round of play
        time(&start);
        int counter = 0;
        // Loop for one game:
        do {

            // get the player's move
            int answer;
            do {
                printf("(#Move %d), Enter the number you want to move ( 0 to exit):\n", counter);
                scanf("%d",&answer);
                if (answer >= 0 && answer < row*col)
                    break;
                else
                    printf("Invalid number.\n");
            } while (1);
            if (answer == 0) {
                break;
            }

            int validMove = 0;
            for(int i=0; i<row; i++)                      
            {
                for(int j=0;j<col;j++) 
                {
                    if (p[i][j] == answer) {
                        // Check the validity of the movement
                        if (abs(i-emptyPositionRow) + abs(j - emptyPositionCol) == 1) {
                            validMove = 1;
                            p[emptyPositionRow][emptyPositionCol] = p[i][j];
                            p[i][j] = 0;
                            emptyPositionRow = i;
                            emptyPositionCol = j;
                            counter++;

                            // Show the board on the screen
                            printTable(row, col, p);

                            // Check if the game is over
                            int checker = 1;

                            for(int i=0; i<row; i++)                      
                            {
                                for(int j=0;j<col;j++) 
                                {
                                    
                                    if (p[i][j] != checker)
                                    {
                                       break; 
                                    }
                                    checker++;
                                    if (checker == row*col)
                                    {
                                        won = 1;
                                    }
                                    
                                }
                                if (won == 1)
                                {
                                    break;
                                }
                            }
                            
                            // Game is over and the player wins
                            if (won == 1) {
                                time(&end);
                                double t = difftime(end,start);
                                printf("Excellent!!! you solved it with %d guesses, in %3.0f seconds.\n",counter, t);
                                break;
                            }

                        }
                        // Invalid movement
                        else {
                            printf("This cell can't move!\n");
                        }
                        break;
                    }
                }
                if (validMove == 1 || won == 1) {
                    break;
                }
            }

        } while (!won);

        // Ask the user to play again or not
        printf("To play again, enter 1:\n");
        int answer;
        scanf("%d",&answer);
        if (answer != 1) {
            break;
        }
    } while (1);

    printf("GoodBye!\n");

    return 0;

}

void printTable(int rows, int cols, int array[rows][cols]){

    for(int i=0; i<rows; i++)                      //output the array
    {
        printf("| ");
        for(int j=0;j<cols;j++) 
        {
            if (array[i][j] == 0)                   //for the 0 prints empty space instead
            {
                printf("   | ");
            }
            else
            {
                printf("%2d | ", array[i][j]);
            }
            
        }
        printf("\n");
    }

}

void fillArray(int row, int col, int array[row][col]){          
    array[0][0] = MyRand(1, (row*col)-1);

    int curRow = 0;
    int curCol = 1;
    int flag = 1;
    while (flag == 1){
        int e = MyRand(1, (row*col)-1);                     //generate random number and check if it is unique
        if (!exists(row, col, e, array)) {
            array[curRow][curCol] = e;
            if (curCol == col-1)
            {
                curCol = 0;
                curRow++;
            }
            else
            {
                curCol++;
                
            }
        }

        if (curRow == row-1 && curCol == col -1)            //loops until reaching last spot in the array
        {
            flag = 0;
        }
    } 
}

int MyRand(int min, int max) {

    int range = max-min+ 1;

    return rand() % range + min;
}

int exists(int row, int col, int num, int array[row][col]) {

    for(int i=0; i<row; i++)                                    //loop through all the array elements and check if number already exists          
    {
        for(int j=0; j<col;j++) 
        {
            if (array[i][j] == num) {
                return 1;
                
            }
        }
    }
    return 0;
}
