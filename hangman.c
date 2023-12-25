//
// Created by corentin on 18/12/23.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hangman.h"
#define MAXCHAR 100



char **openAndReadCsv(char *difficulty, char *fileName)
{
    FILE *inputFile = fopen(fileName, "r");


    if(inputFile == NULL)
    {
        printf("Cannot open file %s",  fileName);
        exit(-1);
    }
    if(my_strcmp(difficulty, "facile") != 0 && my_strcmp(difficulty, "moyen") != 0 && my_strcmp(difficulty, "difficile") != 0)
    {
        printf("Utiliser une entrée valide: \"facile\", \"moyen\", \"difficile\"");
    }


    char row[MAXCHAR];
    char **arrayString = malloc(sizeof (char*) * sizeof row);
    int i = 0;


    while(fgets(row, sizeof(row), inputFile) != NULL) {
        if (strchr(row, '#') != NULL) {
            continue;
        }
        if (strstr(row, difficulty) != NULL) {
            arrayString = malloc(sizeof(char) * length(row) + 1);
            arrayString[i] = row;
            i++;
        }
    }
    return arrayString;
}

char *chooseWord(char **strArray)
{
    int i = 0;
    char *found;
    printf("%s", *strArray);


    return found;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    char **stringsFound = openAndReadCsv("facile", "dictionnary.csv");
    char *wordToGuess = chooseWord(stringsFound);


    return 0;
}