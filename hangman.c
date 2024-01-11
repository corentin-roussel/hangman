//
// Created by corentin on 18/12/23.
//

#include <stdio.h>
#include <string.h>
#include "hangman.h"
#include <time.h>

#define BUF_SIZE 1000

int find_lines(char *inputFile)
{
    int lines = 1;
    int ch = 0;

    FILE *read = fopen(inputFile, "r");

    while(!feof(read))
    {
        ch = fgetc(read);
        if(ch == '#')
        {
            lines--;
        }
        if(ch == '\n')
        {
            lines++;
        }
    }

    return lines;
}


char **openAndReadCsv(char *difficulty, char *fileName, char *category)
{
    int rowCount = 0;

    if(fileName == NULL)
    {
        fileName = "dictionnary.csv";
    }
    FILE *inputFile = fopen(fileName, "r");
    if(inputFile == NULL)
    {
        printf("Cannot open file %s\n",  fileName);
        exit(0);
    }
    if(difficulty == NULL && category != NULL)
    {
        printf("Make sure to enter a valid difficulty: facile, moyen, difficile.\n");
        exit(0);
    }

    int index = 0;
    int lines = find_lines(fileName);

    char row[BUF_SIZE];
    char **array = malloc(lines * sizeof (char*) * 1);;
    int i = 0;
    while(fgets(row, sizeof(row), inputFile) != NULL) {
        rowCount++;

        char **splitted = split(row);
        while(splitted[index] != 0)
        {
            index++;
        }
        if(index != 4)
        {
            if (strchr(row, '#') != NULL) {
                continue;
            }
            printf("Error on row %d: %s\n", rowCount, row);
        }
        if (strchr(row, '#') != NULL) {
            continue;
        }
        if(category == NULL && difficulty == NULL)
        {
            if(strstr(row, "facile") == NULL && strstr(row, "moyen") == NULL && strstr(row, "difficile") == NULL) {
                printf("Error on line %d: %s\n", rowCount, row);
                printf("\n");
                continue;
            }
            char *newString = malloc(strlen(row) + 1);
            strcpy(newString, row);
            array[i] = newString;
            i++;
        }
        if(difficulty != NULL)
        {
            if(strstr(row, "facile") == NULL && strstr(row, "moyen") == NULL && strstr(row, "difficile") == NULL) {
                printf("Error on line %d: %s\n", rowCount, row);
                printf("\n");
            }
            if(strstr(row, difficulty) != NULL) {

                if(category != NULL)
                {
                    if(strstr(row, category) != NULL)
                    {
                        char *newString = malloc(strlen(row) + 1);
                        strcpy(newString, row);
                        array[i] = newString;
                        i++;
                    }
                }
                else{
                    char *newString = malloc(strlen(row) + 1);
                    strcpy(newString, row);
                    array[i] = newString;
                    i++;
                }
            }
        }
        index = 0;
    }
    array[i] = NULL;

    int closeFile = fclose(inputFile);

    if(closeFile == EOF)
    {
        fprintf(stderr, "Erreur durant la fermeture du fichier");
        exit(-1);
    }

    return array;
}


void free_strings(char *string)
{
    free(string);
}

void free_array_strings(char **string)
{
    int i = 0;

    while(string[i] != NULL)
    {
        free(string[i]);
        i++;
    }
    free(string);
}

void printHangmanStand(int numLines)
{
    while(numLines > 0)
    {
        printf("|\n");
        numLines --;
    }
}

void print_hangman(int index)
{
    switch (index)
    {
        case 6:
            printf("|\\___\n");
            printHangmanStand(4);
            break;

        case 5:
            printf("|\\___\n");
            printf("|   O\n");
            printHangmanStand(3);
            break;

        case 4:
            printf("|\\___\n");
            printf("|   O\n");
            printf("|   |\n");
            printHangmanStand(2);
            break;

        case 3:
            printf("|\\___\n");
            printf("|   O\n");
            printf("|  /| \n");
            printHangmanStand(2);
            break;

        case 2:
            printf("|\\___\n");
            printf("|   O\n");
            printf("|  /|\\\n");
            printHangmanStand(2);
            break;

        case 1:
            printf("|\\___\n");
            printf("|   O\n");
            printf("|  /|\\\n");
            printf("|  /    \n");
            printHangmanStand(1);
            break;

        case 0:
            printf("|\\___\n");
            printf("|   O\n");
            printf("|  /|\\\n");
            printf("|  / \\\n");
            printHangmanStand(1);
            break;
        default:
            printf("Error: switch case not met\n\n");
    }
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

    int i =0;
    while(strArray[i] != 0)
    {
        i++;
    }

    srand(time(NULL));

    int random =   0 + rand()  / (RAND_MAX / ((i-1) -0 +1 ) + 1);

    char *found = malloc(sizeof(char*) * length(strArray[random]));

    strcpy(found, strArray[random]);

    char **splitted = split(found);

    free_array_strings(strArray);
    free_strings(found);

    return splitted[0];
}

int replay(void(*hangman)(char *dictionnary ,char *difficulty, char *category), char *dictionnary, char *difficulty, char *category, int gameStatus)
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
            hangman(dictionnary, difficulty, category);
        } else if(buffer == 'N'){
            gameStatus = 0;
            hangman(dictionnary, difficulty, category);
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

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

}

char askUser(int life, char *wordToFind, char buffer)
{
    print_hangman(life);
    printf("You have %d life\n", life);
    printf("Word to find : %s\n", wordToFind);
    printf("Please enter a letter: ");
    scanf("%c", &buffer);
    vider_buffer();

    return buffer;
}




void hangman(char *dictionnary, char *difficulty, char *category)
{
    int gameStatus = 1;
    int life = 6;
    char buffer = '\0';
    int index = 0;
    int fail = 0;
    int firstTurn = 0;
    char letterProposed[50];

    char **stringsFound = openAndReadCsv(difficulty, dictionnary, category);

    char *wordToGuess = chooseWord(stringsFound);

    char *wordToFind = malloc( sizeof(char) * length(wordToGuess));

    wordToFind = wordTransformed(wordToGuess, wordToFind);

    while(gameStatus)
    {
        printf("Letter already entered : ");
        for(int i =0;i < firstTurn; i++)
        {
            printf("%c, ", letterProposed[i]);
        }
        printf("\n");
        buffer = askUser(life, wordToFind, buffer);
        letterProposed[firstTurn] = buffer;
        clear_screen();
        while(wordToFind[index] != '\0')
        {
            if(buffer == wordToGuess[index])
            {
                wordToFind[index] = buffer;
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

        if(my_strcmp(wordToGuess, wordToFind) == 0)
        {
            printf("Congratulations you've won your word was: %s\n", wordToFind);
            gameStatus = replay(hangman, dictionnary, difficulty, category, gameStatus);
        }
        if(life == 0)
        {
            print_hangman(life);
            printf("Ho no you lost your word was %s\n", wordToGuess);
            gameStatus = replay(hangman, dictionnary, difficulty, category,gameStatus);
        }
        firstTurn++;
    }
    free_strings(wordToFind);
}




int main(int argc, char **argv)
{

    if(argc < 2)
    {
        argv[1] = NULL;
        argv[2] = NULL;
        argv[3] = NULL;
    }
    printf("Please make sure you're input is the same as this one: make run, optional command: \"dictionnary.csv <facile/moyen/difficile> category\"\n");

    hangman(argv[1], argv[2], argv[3]);

    return 0;
}