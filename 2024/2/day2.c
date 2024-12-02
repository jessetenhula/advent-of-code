#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Advent of Code 2024 Day 2

Part 1 answer: 213
part 2 answer: 285
*/

int readFileInput(int array[][100]);

int arrayDifferBy(int array[], int length, int minDifference, int maxDifference);
int arrayIsMonotone(int array[], int length);
int checkSingleLevelRemovedArray(int array[], int length);

int listLength(int array[]);
void spliceArray(int destArray[], int srcArray[], int pos, int length) ;

int main()
{
    int numList[1000][100] = {};

    readFileInput(numList);

    int numListLength = 0;
    int safeListCount = 0;
	int safeListLevelRemovedCount = 0;
    for(int i = 0; i < 1000; i++){
        numListLength = listLength(numList[i]);
        if(arrayIsMonotone(numList[i], numListLength) && arrayDifferBy(numList[i], numListLength, 1, 3)) {
            safeListCount++;
        } else {
            if(checkSingleLevelRemovedArray(numList[i], numListLength)) {
                safeListLevelRemovedCount++;
            }
        }
    }

    printf("Part 1: The number of safe lists is: %d\nPart 2: The number of safe lists is: %d", safeListCount, safeListCount + safeListLevelRemovedCount);

    return 0;
}

int readFileInput(int array[][100]) {
    FILE* input = fopen("input.txt", "r");

    if(input == NULL) {
        printf("error opening file");
        return 1;
    }

    int i = 0;
    int j = 0;
    char* token;
    char buffer[100] = {""};
    while(fgets(buffer, 100, input) != NULL){
        token = strtok(buffer, " ");

        j = 0;
        while(token != NULL) {
            sscanf(token, "%d", &array[i][j]);
            token = strtok(NULL, " ");
            j++;
        }
        array[i][j] = -1; // Terminate each list with -1.
        i++;
    }

    fclose(input);

    return 0;
}


int arrayIsMonotone(int array[], int length) {
    int isIncreasing = 1;
    for(int i = 0; i < length - 1; i++) {
        if(!(array[i + 1] > array[i])) {
            isIncreasing = 0;
            break;
        }
    }

    int isDecreasing = 1;
    for(int i = 0; i < length - 1; i++) {
        if(!(array[i + 1] < array[i])) {
            isDecreasing = 0;
            break;
        }
    }

    return isIncreasing + isDecreasing;
}

int arrayDifferBy(int array[], int length, int minDifference, int maxDifference) {
    int result = 1;
    for(int i = 0; i < length - 1; i++) {
        if(abs(array[i] - array[i +1]) > maxDifference || abs(array[i] - array[i +1]) < minDifference) {
            result = 0;
            break;
        }
    }

    return result;
}

int checkSingleLevelRemovedArray(int array[], int length) {
    int result = 0;

    int splicedArray[100] = {};
    for(int i = 0; i < length; i++) {
        spliceArray(splicedArray, array, i, length + 1);

        if(arrayIsMonotone(splicedArray, length - 1) && arrayDifferBy(splicedArray, length - 1, 1, 3)) {
            result = 1;
            break;
        }
    }

    return result;
}

int listLength(int array[]) {
    int count = 0;

    while(array[count] != -1) {
        count++;
    }

    return count;
}

void spliceArray(int destArray[], int srcArray[], int pos, int length) {
    for(int i = 0; i < length; i++){
        destArray[i] = srcArray[i];
    }

    for(int i = pos; i < length; i++) {
        destArray[i] = destArray[i + 1];
    }

}
