#include <stdio.h>
#include <stdlib.h>
#include <string.h

/*
Advent of Code 2024 Day 5
*/

int readMiddleNumbers();
int isInArray(int n, int array[], int startIndex, int length);

int main()
{
    readMiddleNumbers();

    return 0;
}


int readMiddleNumbers()
{
    FILE *input = fopen("input.txt", "r");

    if (input == NULL) {
        printf("error opening file");
        return 1;
    }

    int array[100][100] = {0};
    int left = 0;
    int right = 0;
    int length = 0;

    char buffer[100] = "";
    char* token;

    int fileSection = 0;

    int total = 0;
    int incorrectTotal = 0;

    while(fgets(buffer, 100, input) != NULL) {
        if(buffer[0] == '\n') {
            fileSection = 1;
            continue; // Avoid reading empty line into token
        }
        if(fileSection == 0) {
            sscanf(buffer, "%d|%d\n", &left, &right);
            printf("left: %d, right %d\n", left, right);
            length = array[left][0];
            array[left][length + 1] = right;
            array[left][0]++;
        }
        else {
            int tempArray[100] = {0};
            int tempLength = 0;

            token = strtok(buffer, ",");
            while(token != NULL) {
                sscanf(token, "%d", &tempArray[tempLength]);
                printf("%d ", tempArray[tempLength]);
                token = strtok(NULL, ",");
                tempLength++;
            }
            printf("\n");

            int result = 1;
            for(int i = 0; i < tempLength - 1; i++) {
                int currentNumber = tempArray[i];
                int nextNumber = tempArray[i + 1];

                if(!isInArray(nextNumber, array[currentNumber], 1, array[currentNumber][0])) {
                    result = 0;
                }
            }
            if(result == 1) {
                total += tempArray[tempLength / 2];
            } else {
                for(int i = 0; i < tempLength - 1; i++) {
                    for(int j = 0; j < tempLength - 1 - i; j++) {
                        int currentNumber = tempArray[j];
                        int nextNumber = tempArray[j + 1];
                        int tempNumber = 0;

                        if(!isInArray(nextNumber, array[currentNumber], 1, array[currentNumber][0])) {
                            tempNumber = nextNumber;
                            tempArray[j + 1] = tempArray[j];
                            tempArray[j] = tempNumber;
                        }
                    }
                }
                incorrectTotal += tempArray[tempLength / 2];
            }
        }
    }

    fclose(input);

    printf("Part 1: %d\n", total);
    printf("Part 2: %d", incorrectTotal);

    return 0;
}

int isInArray(int n, int array[], int startIndex, int length) {
    int result = 0;

    for(int i = startIndex; i < length + startIndex; i++){
        if(n == array[i]) {
            result = 1;
        }
    }

    return result;
}
