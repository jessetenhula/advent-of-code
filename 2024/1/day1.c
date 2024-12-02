#include <stdio.h>
#include <stdlib.h>

/*
Advent of code 2024 Day 1

Part 1 answer: 3246517
Part 2 answer: 29379307
*/

int readFileIntoLists(int array1[], int array2[], int length);
void bubbleSort(int array[], int array_length);
int compareListDifference(int array1[], int array2[], int length);
int compareListSimilarity(int array1[], int array2[], int length);


int main()
{
    int list1[1000] = {};
    int list2[1000] = {};

    readFileIntoLists(list1, list2, 1000);

    bubbleSort(list1, 1000);
    bubbleSort(list2, 1000);

    printf("Difference between lists: %d", compareListDifference(list1, list2, 1000));

    printf("\nSimilarity of the lists: %d", compareListSimilarity(list1, list2, 1000));

    return 0;
}

int readFileIntoLists(int array1[], int array2[], int length){
    FILE* list = fopen("input.txt", "r");

    if(list == NULL){
        printf("error opening file");
        return 1;
    }

    for(int i = 0; i < length; i++){
        fscanf(list, "%d %d", &array1[i], &array2[i]);
    }

    fclose(list);

    return 0;
}

void bubbleSort(int array[], int array_length)
{
    int temp = 0;

    for(int i = 0; i < array_length - 1; i++) {
        for(int j = 0; j < array_length - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

int compareListDifference(int array1[], int array2[], int length)
{
    int result = 0;

    for(int i = 0; i < length; i++) {
        result += abs(array2[i] - array1[i]);
    }

    return result;
}

int compareListSimilarity(int array1[], int array2[], int length)
{
    int appearanceCount = 0;
    long result = 0;

    for(int i = 0; i < length; i++) {
        appearanceCount = 0;

        for(int j = 0; j < length; j++) {
            if (array1[i] == array2[j]) {
                appearanceCount++;
            }
        }

        result += (array1[i] * appearanceCount);
    }

    return result;
}
