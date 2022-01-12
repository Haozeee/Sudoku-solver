#include <stdio.h>
int board[9][9];
int i = 0, j = 0;
int main(int argc, char *argv[])
{
    char *text = "input.txt";
    FILE *file = fopen(text, "r");
    if (file == NULL){
        return 1;
    }
    for (int c = fgetc(file); c != EOF; c = fgetc(file)){
        if (c != ' ' && c !='\n'){
            board[i][j] = (int) c - 48;
            if (j==8){
                i ++;
                j = 0;
            }
            else{
                j ++;
            }
        }
    }
    printf("%i\n", board[8][8ma] + 5);
}