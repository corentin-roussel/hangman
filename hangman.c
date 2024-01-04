//
// Created by corentin on 18/12/23.
//

#include <stdio.h>
#include <string.h>
#include "hangman.h"
#include <time.h>
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


    char row[256];
    char **array = malloc(sizeof (char*));
    int i = 0;


    while(fgets(row, sizeof(row), inputFile) != NULL) {
        if (strchr(row, '#') != NULL) {
            continue;
        }
        if(strstr(row, difficulty) != NULL) {
            array = realloc(array, (i + 1) * sizeof(char *));

            array[i] = malloc(strlen(row) + 1);

            strcpy(array[i], row);
            i++;
        }
        
    }
    array[i+1] = NULL;

    fclose(inputFile);

    return array;
}

void vider_buffer(void)
{
    int c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

char *chooseWord(char **strArray)
{
    int startIndex = 0;
    srand(time(NULL));

    char *found = malloc(sizeof(char*) * length(*strArray));

    int random =  startIndex + (rand() % ((sizeof strArray - 1) - startIndex));


    strcpy(found, strArray[random]);

    char **splitted = split(found);

    return splitted[0];
}

int replay(void(*hangman)(char *dictionnary ,char *difficulty), char *dictionnary, char *difficulty, int gameStatus)
{
    char buffer;

    printf("Do you want to replay : Y/N\n");
    scanf("%c", &buffer);
    vider_buffer();
    if(buffer == 'Y') {
        printf("Do you want to change difficulty ? Y/N\n");
        scanf("%c", &buffer);
        vider_buffer();
        if (buffer == 'Y') {
            printf("Choose between: facile, moyen, difficile\n");
            scanf("%s", difficulty);
            vider_buffer();
            gameStatus = 0;
            hangman(dictionnary, difficulty);
        } else if(buffer == 'N'){
            gameStatus = 0;
            hangman(dictionnary, difficulty);
        }else {
            printf("Please choose the appropriate letter next time\n");
            exit(0);
        }
    } else if(buffer == 'N'){
        printf("Thanks for playing\n");
        gameStatus = 0;
    }else {
        printf("Please choose the appropriate letter next time\n");
        exit(0);
    }
    return gameStatus;
}

char *wordTransformed(char *stringTochange, char *emptyString)
{
    int i = 0;
    while(i < length(stringTochange))
    {
        switch (stringTochange[i]) {
            case '-':
                emptyString[i] = '-';
                i++;
                break;
            case ' ':
                emptyString[i] = ' ';
                i++;
                break;
        }

        emptyString[i] = '*';
        i++;
    }
    emptyString[i] = '\0';
    return emptyString;
}

char askUser(int life, char *wordToFind, char buffer)
{
    printf("You have %d life\n", life);
    printf("Word to find : %s\n", wordToFind);
    printf("Please enter a letter: \n");
    scanf("%c", &buffer);
    vider_buffer();

    return buffer;
}


void hangman(char *dictionnary, char *difficulty)
{
    int gameStatus = 1;
    int life = 6;
    char buffer = '\0';
    int index = 0;
    int fail = 0;
    int gameWon = 0;
    int firstTurn = 0;

    char **stringsFound = openAndReadCsv(difficulty, dictionnary);

    char *wordToGuess = chooseWord(stringsFound);

    char *wordToFind = malloc( sizeof(char) * length(wordToGuess));


    wordToFind = wordTransformed(wordToGuess, wordToFind);

    while(gameStatus)
    {
        buffer = askUser(life, wordToFind, buffer);

        while(wordToFind[index] != '\0')
        {
            if(wordToFind[index] == ' ' || wordToFind[index] == '-')
            {
                if(firstTurn == 0)
                {
                    gameWon++;
                }
            }
            if(wordToFind[index] == buffer)
            {
                gameWon--;
            }
            if(buffer == wordToGuess[index])
            {
                wordToFind[index] = buffer;

                gameWon++;
                fail++;
            }

            index++;
        }

        if(fail == 0)
        {
            life--;
        }
        fail = 0;
        index = 0;

        if(gameWon == length(wordToGuess))
        {
            printf("Congratulations you've won your word was: %s\n", wordToFind);
            gameStatus = replay(hangman, dictionnary, difficulty, gameStatus);
        }
        if(life == 0)
        {
            printf("Ho no you lost your word was %s\n", wordToGuess);
            gameStatus = replay(hangman, dictionnary, difficulty, gameStatus);
        }
        firstTurn++;

    }
}




int main(int argc, char **argv)
{
    if(argc < 3)
    {
        exit(-1);
    }

    hangman(argv[1], argv[2]);

    return 0;
}