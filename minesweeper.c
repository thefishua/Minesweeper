// program mimicks the game minesweeper made in 1992
// with a 2d array acting as a minefield.
// The program contains functions to detect mines
// that are inputted by the user and also
// revealing functions such as reveal square and reveal radial
// that reveals sections in the 2d array where there are no mines.
// A game is lost when a mine is revealed ending the program, but
// a game is won when all spaces in the 2d array are revealed and
// there is only mines left in the board
//
// This program was written by Joshua Fish (z5311886)
// on 09/03/20 till 29/03/20
//
// Version 1.0.0 (2020-03-08): Assignment released.
// Version 1.0.1 (2020-03-08): Fix punctuation in comment.
// Version 1.0.2 (2020-03-08): Fix second line of header comment to say minesweeper.c

#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE 8

// The possible command codes.
#define DETECT_ROW              1
#define DETECT_COL              2
#define DETECT_SQUARE           3
#define REVEAL_SQUARE           4
#define GAMEPLAY_MODE           5
#define DEBUG_MODE              6
#define REVEAL_RADIAL           7

// Add any extra #defines here.
#define TOTAL_HINT              3
#define SQUARE_SIZE             3
#define NO_MINE                 0
#define MINE_DETECTED           1
#define WIN                     1
#define LOSS                    -1
#define PLAYING                 0
#define GAME_FIELD              1
#define DEBUG_FIELD             0
void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);

// Place your function prototyes here.
void find_mines_by_row (int minefield[SIZE][SIZE], int row);
void find_mines_by_column (int minefield[SIZE][SIZE], int col);
int find_mines_by_square (int minefield[SIZE][SIZE], int row, int col, int size, int total);
int reveal_square (int minefield[SIZE][SIZE], int row, int col);
void print_gameplay_mode_minefield(int minefield[SIZE][SIZE], int loss);
void check_hint (int minefield[SIZE][SIZE], int user_hint, int command);
int check_field (int minefield[SIZE][SIZE], int game_counter, int loss);
int check_win (int minefield[SIZE][SIZE]);
int check_loss (int minefield[SIZE][SIZE], int row, int col, int command);
void radial (int minefield[SIZE][SIZE], int row, int col);
int reveal_radial (int minefield[SIZE][SIZE], int row, int col);
int valid_condition (int row, int col);
int main(void) {
    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    int number_mines;
    printf("How many mines? ");
    scanf("%d", &number_mines);
    printf("Enter pairs:\n");
    int row = 0;
    int col = 0;
    int counter_mines = 0;
    while (counter_mines < number_mines) {
        scanf("%d %d", &row, &col);
        // Coordinates are valid within the valid_condition function
        if (valid_condition(row, col)) {
            minefield[row][col] = HIDDEN_MINE;
        }
        counter_mines++;
    }
    //Prints out minefield
    printf("Game Started\n");
    print_debug_minefield(minefield);
    
    // TODO: Scan in commands to play the game until the game ends.
    // A game ends when the user wins, loses, or enters EOF (Ctrl+D).
    // You should display the minefield after each command has been processed.
    int command;
    int size = 0;
    int total = 0;
    int win = 0;
    int loss = 0;
    int game_counter = 0;
    int user_hint = 0;
    int scan_value = scanf("%d", &command);
    // If a scan_value is inputted by user
    // then it will allocate the input to the specific command
    // Outputting the command selected
    while (scan_value == 1) {
        // DETECT_ROW commmand
        // Detects the amount of mines within a row
        // Outputting the amount of mine(s) to the user
        if (command == DETECT_ROW) {
            scanf("%d", &row);
            if (user_hint < TOTAL_HINT) {
                find_mines_by_row(minefield, row);
            } else {
                check_hint (minefield, user_hint, command);
            }
            check_field (minefield, game_counter, loss);
            user_hint++;
            // DETECT_COLUMN command
            // Detects the amount of mines within a column
            // Outputting the amount of mine(s) to the user
        } else if (command == DETECT_COL) {
            scanf("%d", &col);
            if (user_hint < TOTAL_HINT) {
                find_mines_by_column(minefield, col);
            } else {
                check_hint (minefield, user_hint, command);
            }
            check_field (minefield, game_counter, loss);
            user_hint++;
            // DECECT_SQUARE command
            // Detects the amount of mine(s) within the minefield
            // Within a sized square deteremined by the user
            // Outputting the amount of mine(s) in the specific square
        } else if (command == DETECT_SQUARE) {
            scanf("%d %d %d", &row, &col, &size);
            if (user_hint < TOTAL_HINT) {
                total = find_mines_by_square(minefield, row, col, size, total);
                printf("There are %d mine(s) in the square centered at row %d,"
                " column %d of size %d\n", total, row, col, size);
            } else {
                check_hint (minefield, user_hint, command);
            }
            check_field (minefield, game_counter, loss);
            user_hint++;
            // REVEAL_SQUARE command
            // Uses the find_mines_by_square function and
            // Outputs it a size 3 square to the user
        } else if (command == REVEAL_SQUARE) {
            scanf("%d %d", &row, &col);
            loss = check_loss (minefield, row, col, command);
            win = check_win (minefield);
            // A loss has occured within the game
            if (loss <= LOSS) {
                printf("Game Over\n");
                check_field(minefield, game_counter, loss);
                return 0;
            }
            // A win has occured within the game
            if (win == WIN) {
                printf("Game Won!\n");
                check_field(minefield, game_counter, loss);
                return 0;
            }
            check_field (minefield, game_counter, loss);
            // REVEAL RADIAL command
            // Outputs a radial to the user
        } else if (command == REVEAL_RADIAL) {
            scanf("%d %d", &row, &col);
            loss = check_loss (minefield, row, col, command);
            win = check_win (minefield);
            // A loss has occured within the game
            if (loss <= LOSS) {
                printf("Game Over\n");
                check_field(minefield, game_counter, loss);
                return 0;
            }
            // A win has occured within the game
            if (win == WIN) {
                printf("Game Won!\n");
                check_field(minefield, game_counter, loss);
                return 0;
            }
            check_field (minefield, game_counter, loss);
            // GAMEPLAY_MODE command
            // Outputs the gameplay field to the user
        } else if (command == GAMEPLAY_MODE) {
            printf("Gameplay mode activated\n");
            print_gameplay_mode_minefield(minefield, loss);
            game_counter = GAME_FIELD;
    
            // DEBUG_MODE command
            // Outputs the debug mode to the user
        } else if (command == DEBUG_MODE) {
            printf("Debug mode activated\n");
            print_debug_minefield(minefield);
            game_counter = DEBUG_FIELD;
        }
        scan_value = scanf("%d", &command);
    }
    
    
       
    
    
    return 0;
}
// Function that holds the valid condition
// Allowing only valid inputs within the minefield
int valid_condition (int row, int col) {
    int condition = row >= 0 && row < SIZE && col >= 0 && col < SIZE;
    return condition;
}
// Function to detect amount of mines in a row
// The function goes through the 2D array and
// increments a total of mines whenever a mine is detected
// Ouputting a statement to the user of the amount of mine(s) in the row
void find_mines_by_row (int minefield[SIZE][SIZE], int row) {
    int curr_row = 0;
    int total = 0;
    while (curr_row < SIZE - 1) {
        if (minefield[row][curr_row] == HIDDEN_MINE) {
            total++;
        }
        curr_row++;
    }
    printf("There are %d mine(s) in row %d\n", total, row);
}
// Function to detect amount of mines in a column
// The function goes through the 2D array and
// increments a total of mine(s) whenever a mine is detected
// Ouputting a statement to the user of the amount of mine(s) in the column
void find_mines_by_column (int minefield[SIZE][SIZE], int col) {
    int curr_col = 0;
    int total = 0;
    while (curr_col < SIZE - 1) {
        if (minefield[curr_col][col] == HIDDEN_MINE) {
            total++;
        }
        curr_col++;
    }
    printf("There are %d mine(s) in column %d\n", total, col);
}

// Function to detect amount of mines in a Square
// The function creates a square within the 2D array
// incrementing a total of mine(s) whenever a mine is detected in the square
// Outputting a statement to the user of the amount of mine(s) in the square
int find_mines_by_square (
    int minefield[SIZE][SIZE],
    int row, int col,
    int size, int total)
    {
    
    int start_row = row - size / 2;
    int start_col = col - size / 2;
    
    int end_row = row + size / 2;
    int end_col = col + size / 2;
    
    if (start_row < 0) {
        start_row = 0;
    }
    
    if (start_col < 0) {
        start_col = 0;
    }
    
    if (end_row > SIZE - 1) {
        end_row = SIZE - 1;
    }
    
    if (end_col > SIZE - 1) {
        end_col = SIZE - 1;
    }
    
    int curr_row = start_row;
    while (curr_row <= end_row) {
        int curr_col = start_col;
        while (curr_col <= end_col) {
            if (minefield[curr_row][curr_col] == HIDDEN_MINE) {
                total++;
            }
            curr_col++;
        }
        curr_row++;
    }
    

    return total;
}
// Function that creates the radial shape
void radial (int minefield[SIZE][SIZE], int row, int col) {
    
    int counter_row = row;
    int counter_col = col;
    int total = 0;
    
    // Radial shape is diagonal upper left
    while (valid_condition(row, col) && total == NO_MINE) {
        row--;
        col--;
        if (valid_condition(row, col) && total == NO_MINE) {
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (minefield[row][col] != HIDDEN_MINE) {
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
    row = counter_row;
    col = counter_col;
    if (total > NO_MINE) {
        total = NO_MINE;
    }
    // Radial shape is diagonal upper right
    while (valid_condition(row, col) && total == NO_MINE) {
        row--;
        col++;
        if (valid_condition(row, col) && total == NO_MINE) {
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (minefield[row][col] != HIDDEN_MINE) {
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
    row = counter_row;
    col = counter_col;
    if (total > NO_MINE) {
        total = NO_MINE;
    }
    
    // Radial shape is straight up
    while (valid_condition(row, col) && total == NO_MINE) {
        row--;
        if (valid_condition(row, col) && total == NO_MINE) {
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (minefield[row][col] != HIDDEN_MINE) {
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
    row = counter_row;
    col = counter_col;
    if (total > NO_MINE) {
        total = NO_MINE;
    }
    
    // Radial shape is straight down
    while (valid_condition(row, col) && total == NO_MINE) {
        row++;
        if (valid_condition(row, col) && total == NO_MINE) {
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (minefield[row][col] != HIDDEN_MINE) {
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
    row = counter_row;
    col = counter_col;
    if (total > NO_MINE) {
        total = NO_MINE;
    }
    // Radial shape is straight left
    while (valid_condition(row, col) && total == NO_MINE) {
        col--;
        if (valid_condition(row, col) && total == NO_MINE) {
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (minefield[row][col] != HIDDEN_MINE) {
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
    row = counter_row;
    col = counter_col;
    if (total > NO_MINE) {
        total = NO_MINE;
    }
    //Radial shape is straight right
    while (valid_condition(row, col) && total == NO_MINE) {
        col++;
        if (valid_condition(row, col) && total == NO_MINE) {
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (minefield[row][col] != HIDDEN_MINE) {
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
    row = counter_row;
    col = counter_col;
    // Radial shape is diagonal lower left
    while (valid_condition(row, col) && total == NO_MINE) {
        row++;
        col--;
        if (valid_condition(row, col) && total == NO_MINE) {
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (minefield[row][col] != HIDDEN_MINE) {
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
    row = counter_row;
    col = counter_col;
    if (total > NO_MINE) {
        total = NO_MINE;
    }
    // Radial shape is diagonal lower right
    while (valid_condition(row, col) && total == NO_MINE) {
        row++;
        col++;
        if (valid_condition(row, col) && total == NO_MINE) {
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (minefield[row][col] != HIDDEN_MINE) {
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
}
// Function to reveal the square to the user
int reveal_square (int minefield[SIZE][SIZE], int row, int col) {
    
    int total = 0;
    int loss = 0;
    int size = SQUARE_SIZE;
    
    
    int start_row = row - size / 2;
    int start_col = col - size / 2;
    
    int end_row = row + size / 2;
    int end_col = col + size / 2;
    // Valid conditions for the starting and ending column and row
    if (start_row < 0) {
        start_row = 0;
    }
    
    if (start_col < 0) {
        start_col = 0;
    }
    
    if (end_row > SIZE - 1) {
        end_row = SIZE - 1;
    }
    
    if (end_col > SIZE - 1) {
        end_col = SIZE - 1;
    }
    
    int curr_row = start_row;
    while (curr_row <= end_row) {
        int curr_col = start_col;
        while (curr_col <= end_col) {
            // Loss game if a mine is detected where user has inputted
            if (minefield[row][col] == HIDDEN_MINE) {
                loss--;
                break;
            }
            // Detects if a mine is adjacent to the square
            // Output is a single VISIBLE SAFE where user has inputted
            total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
            if (total >= MINE_DETECTED) {
                minefield[row][col] = VISIBLE_SAFE;
                total = NO_MINE;
                // If a mine is not detected
                // Output is a 3x3 square
            } else if (minefield[curr_row][curr_col] != HIDDEN_MINE && total == NO_MINE) {
                minefield[curr_row][curr_col] = VISIBLE_SAFE;
            }
            curr_col++;
        }
        curr_row++;
    }
    return loss;
}
// Function that ouputs reveals a radial to the user
int reveal_radial (int minefield[SIZE][SIZE], int row, int col) {
    // Revealing a square
    int loss = 0;
    int total = 0;
    loss = reveal_square (minefield, row, col);
    total = find_mines_by_square (
            minefield, row, col,
            SQUARE_SIZE, total
            );
    // Revealing a radial
    // Only if no mine is detected within the square
    if (total == NO_MINE && loss == PLAYING) {
        radial (minefield, row, col);
    }
    return loss;
}

// Function that checks if loss has occured
int check_loss (int minefield[SIZE][SIZE], int row, int col, int command) {
    int loss = 0;
    if (command == REVEAL_RADIAL) {
        loss = reveal_radial (minefield, row, col);
    }
    if (command == REVEAL_SQUARE) {
        loss = reveal_square(minefield, row, col);
    }
    return loss;
}
// Function that check if win has occured

int check_win (int minefield[SIZE][SIZE]) {
    
    int win = WIN;
    
    int curr_row = 0;
    while (curr_row < SIZE) {
        int curr_col = 0;
        while (curr_col < SIZE) {
            if (minefield[curr_row][curr_col] == HIDDEN_SAFE) {
                win = PLAYING;
            }
            curr_col++;
        }
        curr_row++;
    }
    
    return win;
}
// Function that checks what field the user is using at the current period
int check_field (int minefield[SIZE][SIZE], int game_counter, int loss) {
    if (game_counter == DEBUG_FIELD) {
        print_debug_minefield(minefield);
    }
    if (game_counter == GAME_FIELD) {
        print_gameplay_mode_minefield(minefield, loss);
    }
    return game_counter;
}
// Function to check if hints are used up
// If user_hints > 3 outputs message to user
void check_hint (int minefield[SIZE][SIZE], int user_hint, int command) {
    if (user_hint >= TOTAL_HINT && command <= DETECT_SQUARE) {
        printf("Help already used\n");
    }
}

// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}

// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

// Function that prints out GAMEPLAY_MODE
void print_gameplay_mode_minefield(int minefield[SIZE][SIZE], int loss) {
    int total = 0;
    if (loss <= LOSS) {
        printf("xx\n");
        printf("/\\\n");
    } else {
        printf("..\n");
        printf("\\/\n");
    }
    // Gameplay mode layout
    printf("    00 01 02 03 04 05 06 07\n");
    printf("   -------------------------\n");
    int row = 0;
    while (row < SIZE) {
        int col = 0;
        printf("0%d |", row);
        while (col < SIZE) {
            if (minefield [row][col] == VISIBLE_SAFE) {
                total = find_mines_by_square (
                        minefield, row, col,
                        SQUARE_SIZE, total
                        );
                if (total >= MINE_DETECTED) {
                    printf("0%d ", total);
                    total = 0;
                } else {
                    printf("   ");
                }
            }
            if (minefield[row][col] == HIDDEN_SAFE) {
                printf("## ");
            } else if (loss <= LOSS) {
                if (minefield [row][col] == HIDDEN_MINE) {
                    printf("() ");
                }
            } else if (minefield[row][col] == HIDDEN_MINE) {
                printf("## ");
            }
            col++;
            
        }
        printf("|");
        printf("\n");
        row++;
    }
    printf("   -------------------------\n");
}
