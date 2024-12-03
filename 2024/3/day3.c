#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long readFileMul();
int charIsInKeyword(char* inputString, char* compareString, char character, int position, int length);
void clearWord(char* string, int length);

int main()
{
    printf("Part 1: The multiplication result is : %ld", readFileMul(0));
    printf("\nPart 2: The multiplication result is : %ld", readFileMul(1));

    return 0;
}


long readFileMul(int enableDoInstruction) {
    long result = 0;

    FILE* myinput = fopen("input.txt", "r");

    if(myinput == NULL) {
        printf("error opening file");
        return 1;
    }

    char ch = ' ';

    char keyWordMul[4] = {""};
    int mulCount = 0;
    char keyWordDo[5] = {""};
    int doCount = 0;
    char keyWordDont[8] = {""};
    int dontCount = 0;
    int enabled = 1;

    char beginningCh;
    int number1 = 0;
    int number2 = 0;
    char closingCh;
    while((ch = getc(myinput)) != EOF) {

        if(charIsInKeyword(keyWordMul, "mul", ch, mulCount, 4)) {
            mulCount++;
        } else {
            mulCount = 0;
            clearWord(keyWordMul, 4);
        }

        if(enableDoInstruction) {
            if(charIsInKeyword(keyWordDo, "do()", ch, doCount, 5)) {
                doCount++;
            } else {
                doCount = 0;
                clearWord(keyWordDo, 5);
            }

            if(charIsInKeyword(keyWordDont, "don't()", ch, dontCount, 8)) {
                dontCount++;
            } else {
                dontCount = 0;
                clearWord(keyWordDont, 8);
            }

            if(strcmp(keyWordDo, "do()") == 0) {
                enabled = 1;
            } else if(strcmp(keyWordDont, "don't()") == 0) {
                enabled = 0;
            }
        }

        if(strcmp(keyWordMul, "mul") == 0 && enabled) {
            mulCount = 0;
            clearWord(keyWordMul, 4);
            if(fscanf(myinput, "%c%d,%d%c", &beginningCh, &number1, &number2, &closingCh) == 4 && beginningCh == '(' && closingCh == ')') {
                result += number1 * number2;
            }
        }
    }

    return result;
}

int charIsInKeyword(char* inputString, char* compareString, char character, int position, int length) {
    int result = 0;
    if(compareString[position] == character && position < length) {
        result = 1;
        inputString[position] = character;
    }
    return result;
}


void clearWord(char* string, int length) {
    for(int i = 0; i < length - 1; i++){
        string[i] = ' ';
    }
    string[length - 1] = '\0';
}
