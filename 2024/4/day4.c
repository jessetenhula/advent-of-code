#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIDTH 141

/*
Advent of Code 2024 Day 4
*/

int readFileIntoMatrix(char matrix[][141], char* fileName);
int writeMatrixToFileDiagonal(char matrix[][141], char* fileName);
int writeMatrixToFileDiagonalVertical(char matrix[][141], char* fileName);

int searchMatrix(char* keyWord, int keyWordLength, char matrix[][141], int verticalSearch);
int searchMatrixDiagonal(char* keyWord, int keyWordLength, char matrix[][141], int verticalSearch);

int charIsInWord(char* word, char* compareWord, char ch, int index, int length);
void clearWord(char* word, int length);

int main()
{
    char puzzle[WIDTH][WIDTH] = {};
    int total = 0;

    readFileIntoMatrix(puzzle, "input.txt");

    for(int perpendicular = 0; perpendicular < 2; perpendicular++){
        total += searchMatrix("XMAS", 5, puzzle, perpendicular);
        total += searchMatrix("SAMX", 5, puzzle, perpendicular);
        total += searchMatrixDiagonal("XMAS", 5, puzzle, perpendicular);
        total += searchMatrixDiagonal("SAMX", 5, puzzle, perpendicular);
    }

    printf("\nPart 1 total XMAS count: %d", total);
    printf("\nPart 2 total X-MAS count: %d", searchMasX(puzzle));

    return 0;
}

int searchMasX(char matrix[][WIDTH])
{
    int result = 0;
    char ch = ' ';

    for(int x = 1; x < WIDTH - 1; x++) {
        for(int y = 1; y < WIDTH - 1; y++) {
            ch = matrix[x][y];
            if(ch == 'A') {
                int topLeftDiagonal = ((matrix[x - 1][y - 1] == 'M' && matrix[x + 1][y + 1] == 'S') || (matrix[x - 1][y - 1] == 'S' && matrix[x + 1][y + 1] == 'M'));
                int topRightDiagonal = ((matrix[x + 1][y - 1] == 'M' && matrix[x - 1][y + 1] == 'S') || (matrix[x + 1][y - 1] == 'S' && matrix[x - 1][y + 1] == 'M'));
                if(topLeftDiagonal && topRightDiagonal) {
                    result++;
                }
            }
        }
    }

    return result;
}

int searchMatrix(char* keyWord, int keyWordLength, char matrix[][WIDTH], int perpendicular)
{
    int result = 0;
    char keyWordTemp[100] = {""};
    char ch = ' ';
    int count = 0;

    for(int x = 0; x < WIDTH; x++) {
        for(int y = 0; y < WIDTH; y++) {
            if(!perpendicular) {
                ch = matrix[x][y];
            } else {
                ch = matrix[y][x];
            }

            if(charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength)) {
                count++;
            } else {
                count = 0;
                clearWord(keyWordTemp, keyWordLength);
                count = charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength);
            }

            if(strcmp(keyWordTemp, keyWord) == 0) {
                count = 0;
                clearWord(keyWordTemp, keyWordLength);

                result++;
            }
        }
    }

    return result;
}

int searchMatrixDiagonal(char* keyWord, int keyWordLength, char matrix[][WIDTH], int perpendicular)
{
    int result = 0;
    char keyWordTemp[100] = {""};
    char ch = ' ';
    int count = 0;

    if(!perpendicular) {
        for(int y = WIDTH - 1; y > 0; y--) {
            for(int n = 0; n + y < WIDTH; n++) {
                ch = matrix[n][y + n];

                if(charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength)) {
                    count++;
                } else {
                    count = 0;
                    clearWord(keyWordTemp, keyWordLength);
                    count = charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength);
                }

                if(strcmp(keyWordTemp, keyWord) == 0) {
                    count = 0;
                    clearWord(keyWordTemp, keyWordLength);

                    result++;
                }
            }
        }

        for(int x = 0; x < WIDTH; x++) {
            for(int n = 0; n + x < WIDTH; n++) {
                ch = matrix[x + n][n];
                if(charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength)) {
                    count++;
                } else {
                    count = 0;
                    clearWord(keyWordTemp, keyWordLength);
                    count = charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength);
                }

                if(strcmp(keyWordTemp, keyWord) == 0) {
                    count = 0;
                    clearWord(keyWordTemp, keyWordLength);

                    result++;
                }
            }
        }
    } else { //PERPENDICULAR DIAGONAL SEARCH
        for(int x = 0; x < WIDTH; x++) {
            for(int n = 0; n <= x; n++) {
                ch = matrix[x - n][n];

                if(charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength)) {
                    count++;
                } else {
                    count = 0;
                    clearWord(keyWordTemp, keyWordLength);
                    count = charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength);
                }

                if(strcmp(keyWordTemp, keyWord) == 0) {
                    count = charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength);
                    clearWord(keyWordTemp, keyWordLength);

                    result++;
                }
            }
            count = 0;
            clearWord(keyWordTemp, keyWordLength);
        }
        for(int y = 1; y < WIDTH; y++) {
            for(int n = 0; n < WIDTH - y ; n++) {
                ch = matrix[WIDTH - 1 - n][y + n];

                if(charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength)) {
                    count++;
                } else {
                    count = 0;
                    clearWord(keyWordTemp, keyWordLength);
                    count = charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength);
                }

                if(strcmp(keyWordTemp, keyWord) == 0) {
                    count = charIsInWord(keyWordTemp, keyWord, ch, count, keyWordLength);
                    clearWord(keyWordTemp, keyWordLength);

                    result++;
                }
            }
            count = 0;
            clearWord(keyWordTemp, keyWordLength);
        }
    }

    return result;
}

int readFileIntoMatrix(char matrix[][WIDTH], char* fileName)
{
    FILE* input = fopen(fileName, "r");

    if(input == NULL) {
        printf("error opening file");
        return 1;
    }

    char ch = ' ';
    for(int x = 0; x < WIDTH -1; x++) {
        for(int y = 0; y < WIDTH; y++) {
            ch = getc(input);
            matrix[x][y] = ch;
        }
    }

    for(int y = 0; y < WIDTH; y++) {
        matrix[WIDTH -1][y] = '\n';
    }

    fclose(input);

    return 0;
}

int charIsInWord(char* word, char* compareWord, char ch, int index, int length) {
    int result = 0;
    if(compareWord[index] == ch && index < length) {
        result = 1;
        word[index] = ch;
    }
    return result;
}

void clearWord(char* word, int length)
{
    for(int i = 0; i < length - 1; i++) {
        word[i] = ' ';
    }

    word[length - 1] = '\0';
}
