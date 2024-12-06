#include <stdio.h>
#include <stdlib.h>
#define LENGTH 130

/*
Advent of Code 2024 Day 5
*/

typedef struct entity {
    int x;
    int y;
    int dir_x;
    int dir_y;
    char sprite;
} entity;

int readFileIntoMatrix(char matrix[][LENGTH], entity* guard);
int drawEntityPath(char matrix[][LENGTH], entity* guard);
int findObstruction(char matrix[][LENGTH], entity* guard);

void copyMatrix(char copy[][LENGTH], char matrix[][LENGTH]);
void turnRight(entity* ent);
char getSprite(int dir_x, int dir_y);

int main()
{
    char matrix[LENGTH][LENGTH] = {};

    entity* guard = malloc(sizeof(*guard));
    guard->dir_x = 0;
    guard->dir_y = 1;
    guard->sprite = '^';

    readFileIntoMatrix(matrix, guard);
    int origin_x = guard->x;
    int origin_y = guard->y;

    drawEntityPath(matrix, guard);

    char myCopy[LENGTH][LENGTH] = {};

    int result1 = 0;
    int result2 = 0;
    for(int y = LENGTH - 1; y >= 0; y--) {
        for(int x = 0; x < LENGTH; x++) {
            if(matrix[x][y] == 'X' && (x != origin_x || y != origin_y)) {
                result1++;
                copyMatrix(myCopy, matrix);
                myCopy[x][y] = '#';
                guard->x = origin_x;
                guard->y = origin_y;
                guard->dir_x = 0;
                guard->dir_y = 1;
                guard->sprite = '^';

                result2 += findObstruction(myCopy, guard);
            }
        }
    }

    printf("Part 1 total: %d\n", result1 + 1);
    printf("Part 2 total: %d", result2);

    return 0;
}

int findObstruction(char matrix[][LENGTH], entity* guard)
{
    int maxIterations = 9999; // Prevent infinite loop by setting maximum iterations
    // While entity is in bounds
    while(guard->x + guard->dir_x < LENGTH && guard->x + guard->dir_x >= 0 && guard->y + guard->dir_y < LENGTH && guard->y + guard->dir_y >= 0 && maxIterations > 0) {
        maxIterations--;
        // The coordinate the entity will attempt to move to
        int next_x = guard->x + guard->dir_x;
        int next_y = guard->y + guard->dir_y;

        if(matrix[next_x][next_y] != '#') {
            matrix[guard->x][guard->y] = guard->sprite;
            guard->x = next_x;
            guard->y = next_y;
            if(matrix[guard->x][guard->y] == guard->sprite) {
                return 1;
            }
        } else {
            turnRight(guard);
        }
    }

    if (maxIterations == 0) {
        return 1;
    }

    return 0;
}

int drawEntityPath(char matrix[][LENGTH], entity* guard)
{
    // While entity is in bounds
    while(guard->x + guard->dir_x < LENGTH && guard->x + guard->dir_x >= 0 && guard->y + guard->dir_y < LENGTH && guard->y + guard->dir_y >= 0) {
        // The coordinate the entity will attempt to move to
        int next_x = guard->x + guard->dir_x;
        int next_y = guard->y + guard->dir_y;

        if(matrix[next_x][next_y] != '#' && matrix[next_x][next_y] != 'O' ) {
            matrix[guard->x][guard->y] = 'X';
            guard->x = next_x;
            guard->y = next_y;
        } else {
            turnRight(guard);
        }
    }
    matrix[guard->x][guard->y] = 'X'; // Set guard's last position to X
    return 0;
}

int readFileIntoMatrix(char matrix[][LENGTH], entity* guard)
{
    FILE *input = fopen("input.txt", "r");

    if (input == NULL) {
        printf("error opening file");
        return 1;
    }

    char ch = ' ';
    for(int y = LENGTH - 1; y >= 0; y--) {
        for(int x = 0; x < LENGTH + 1; x++) {
            ch = getc(input);
            if(ch != '\n') {
                matrix[x][y] = ch;
            }
            if(ch == '^') {
                guard->x = x;
                guard->y = y;
            }
        }
    }

    fclose(input);

    return 0;
}

void copyMatrix(char copy[][LENGTH], char matrix[][LENGTH])
{
    for(int i = 0; i < LENGTH; i++) {
        for(int j = 0; j < LENGTH; j++) {
            copy[i][j] = matrix[i][j];
        }
    }
}

void turnRight(entity* guard) {
    if(guard->dir_x == 0) {
        guard->dir_x = guard->dir_y;
        guard->dir_y = 0;
    } else if (guard->dir_y == 0) {
        guard->dir_y = -guard->dir_x;
        guard->dir_x = 0;
    }
    guard->sprite = getSprite(guard->dir_x, guard->dir_y);
}

char getSprite(int dir_x, int dir_y) {
    char newSprite;

    if(dir_x == 1) {
        newSprite = '>';
    } else if(dir_x == -1) {
        newSprite = '<';
    } else if(dir_y == 1) {
        newSprite = '^';
    } else if(dir_y == -1) {
        newSprite = 'v';
    }

    return newSprite;
}
