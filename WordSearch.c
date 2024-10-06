#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);
void search(const int Size,char puzzle[][Size],const int wordSize,char* word);
bool inBounds(int row, int col, const int Size);
bool check1D(const int Size, char puzzle[][Size], const int wordSize, char*word, int rowLoc, int colLoc, int dir);

int main(void) {
    const int Size = 20;
    char puzzle[Size][Size];
    readWordPuzzle(Size, puzzle);
    int wordSize = 0;
    char* word = readWord(&wordSize);
    printWordPuzzle(Size, puzzle);
    printf("The word you are looking for is\n");
    printWord(word, wordSize);
    printf("\n");
    printf("Do you want to search? (Y or N)\n");
    char isSearch;
    scanf(" %c", &isSearch);
    if (isSearch == 'Y' || isSearch == 'y') {
        search(Size, puzzle, wordSize, word);
    }
    free(word);
    return 0;
}
char* readWord(int* wordSize)
{
    printf("How many characters are there in the word?\n");
    scanf("%d",wordSize);
    char *word=(char*)malloc((*wordSize+1)*sizeof(char));
    printf("What is the word that you are looking for?\n");
    scanf("%s",word);
    return word;
    
}
void readWordPuzzle(const int Size, char puzzle[][Size])
{
    printf("Please enter the word puzzle:\n");
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            scanf(" %c",&puzzle[i][j]);
        }
    }
}
bool inBounds(int row, int col, const int Size)
{
    return row>=0 && col>=0 && col<Size && row<Size;
}
void printWordPuzzle(const int Size, char puzzle[][Size])
{
    printf("The word puzzle entered is\n");
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            printf("%c ",puzzle[i][j]);
        }
        printf("\n");
    }
}
void printWord(char* word, const int wordSize)
{
    for(int i=0;i<wordSize;i++){
        printf("%c ",word[i]);
    }
}
bool check1D(const int Size, char puzzle[][Size], const int wordSize, char* word, int rowLoc, int colLoc, int dir) {
    int row = rowLoc, col = colLoc;
    int rowDir = 0, colDir = 0;

    switch (dir) {
        case 0: 
            rowDir = -1;
            break;
        case 1: 
            rowDir = -1;
            colDir = 1;
            break;
        case 2:
            colDir = 1;
            break;
        case 3:
            rowDir = 1;
            colDir = 1;
            break;
        case 4: 
            rowDir = 1;
            break;
        case 5:
            rowDir = 1;
            colDir = -1;
            break;
        case 6:
            colDir = -1;
            break;
        case 7:
            rowDir = -1;
            colDir = -1;
            break;
        default:
            return false;
    }

    for (int i = 0; i < wordSize; i++) {
        if (!inBounds(row, col, Size) || puzzle[row][col] != word[i]) {
            return false;
        }
        row += rowDir;
        col += colDir;
    }

    return true;
}
void search(const int Size, char puzzle[][Size], const int wordSize, char* word) {
    const char* directions[] = {"north", "northeast", "east", "southeast", "south", "southwest", "west", "northwest"};

    for (int row = 0; row < Size; ++row) {
        for (int col = 0; col < Size; ++col) {
            for (int dir = 0; dir < 8; ++dir) {
                if (check1D(Size, puzzle, wordSize, word, row, col, dir)) {
                    printf("%s can be found at row , col = (%d, %d) in the %s direction.\n", word, row + 1, col + 1, directions[dir]);
                    return;
                }
            }
        }
    }

    printf("%s cannot be found!\n", word);
}




