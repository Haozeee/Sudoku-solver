#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// Board length
#define N 9

bool used_in_row(int board[N][N], int row, int num);
bool used_in_col(int board[N][N], int col, int num);
bool used_in_box(int board[N][N], int row_start, int col_start, int num);
bool is_safe(int board[N][N], int row, int col, int num);
bool solve(int board[N][N], int row, int col);
void print_board(int board[N][N]);

/* Format for board
int start[N][N] = {{8, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 3, 6, 0, 0, 0, 0, 0},
                   {0, 7, 0, 0, 9, 0, 2, 0, 0},
                   {0, 5, 0, 0, 0, 7, 0, 0, 0},
                   {0, 0, 0, 0, 4, 5, 7, 0, 0},
                   {0, 0, 0, 1, 0, 0, 0, 3, 0},
                   {0, 0, 1, 0, 0, 0, 0, 6, 8},
                   {0, 0, 8, 5, 0, 0, 0, 1, 0},
                   {0, 0, 0, 0, 0, 0, 4, 0, 0}};
*/

int start[N][N]; // Board

int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("Invalid command line arguments\n");
        return 1;
    }

    char *name = argv[1];
    FILE *file = fopen(name, "r");
    if (file == NULL){
        return 1;
    }
    int i = 0, j = 0;
    for (int c = fgetc(file); c != EOF; c = fgetc(file)){
        if (c != ' ' && c !='\n'){
            start[i][j] = (int) c - 48;
            if (start[i][j] > 9 || start[i][j] < 0) {
                printf("Invalid input file\n");
                return 1;
            }
            if (j == 8){
                i ++;
                j = 0;
            }
            else{
                j ++;
            }
        }
    }
    fclose(file);

    clock_t t;
    t = clock();
    if (solve(start, 0, 0)){
        printf("\nSolution:\n\n");
        print_board(start);
    }
    else{
        printf("No solution found.\n");
    }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_taken);
    return 0;
}

// Attempt to fill each empty spot from left to right, up to down
bool solve(int board[N][N], int row, int col)
{
    if (row == N){
        return true;
    }

    if (board[row][col] != 0){ // If spot is not empty, proceed to next spot
        if (col == 8){ // At last column of the row
            if (solve(board, row + 1, 0)){
                return true;
            }
        }
        else{
            if (solve(board, row, col + 1)){
                return true;
            }
        }
        return false;
    }

    for (int num = 1; num <= 9; num++) { // If spot is empty, attempt to solve
        if (is_safe(board, row, col, num)){
            board[row][col] = num;
            if (col == 8){
                if (solve(board, row + 1, 0)){
                    return true;
                }
            }
            else{
                if (solve(board, row, col + 1)){
                    return true;
                }
            }
            board[row][col] = 0;
        }
    }
    return false;
}

// Check row
bool used_in_row(int board[N][N], int row, int num)
{
    for (int i = 0; i < N; i++){
        if (board[row][i] == num){
            return true;
        }
    }
    return false;
}

// Check column
bool used_in_col(int board[N][N], int col, int num)
{
    for (int i = 0; i < N; i++){
        if(board[i][col] == num){
            return true;
        }
    }
    return false;
}

// Check box
bool used_in_box(int board[N][N], int row_start, int col_start, int num)
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[i + row_start][j + col_start] == num){
                return true;
            }
        }
    }
    return false;
}

// Check safe
bool is_safe(int board[N][N], int row, int col, int num)
{
    if (used_in_col(board, col, num)){
        return false;
    }
    if (used_in_row(board, row, num)){
        return false;
    }
    if (used_in_box(board, row - (row % 3), col - (col % 3), num)){
        return false;
    }
    return true;
}

// Print solution
void print_board(int board[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            printf("%i ",board[i][j]);
            if (j == 2 || j == 5){
                printf("| ");
            }
        }
        printf("\n");
        if (i == 2 || i == 5){
            printf("---------------------\n");
        }
    }
}