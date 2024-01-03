//
// Created by corentin on 18/12/23.
//

#ifndef HANGMAN_HANGMAN_H
#define HANGMAN_HANGMAN_H

#include <stdlib.h>
#include <unistd.h>

int num_length(int num)
{
    int i = 0;
    while(num != 0)
    {
        num = num/10;
        i++;
    }

    return i;
}

int length(const char *str)
{
    int i = 0;
    while(str[i] != 0)
    {
        i++;
    }
    return i;
}

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    int num =  0;

    while(s1[i] != 0)
    {
        if(s2[i] != 0) {
            if(s1[i] != s2[i])
            {
                num = (int)s1[i] - (int)s2[i];
                if(num < 0)
                {
                    num = -1;
                    return num;
                }else if (num > 0)
                {
                    num = 1;
                    return num;
                }
            }
            i++;
        }else
        {
            num = 1;
            break;
        }
    }
    if(s2[i] != 0)
    {
        num = -1;
    }
    return num;
}

int my_atoi(char *str)
{
    int i = 0;
    int ascii = 0;

    while(str[i] != '\0')
    {
        ascii = ascii * 10 + (str[i] - '0');
        ++i;
    }
    return ascii;
}

int *number_array(int num)
{
    int i =0;
    int len = num_length(num);
    int *numberArray = malloc(sizeof(int) *len);

    while (i<len)
    {
        numberArray[i] = num % 10;
        num /= 10;
        i++;
    }
    numberArray[i] = '\0';
    return numberArray;
}

char *reverse_string(char *str)
{
    int i = 0;
    int len = length(str);
    char *temp = malloc(sizeof(char));

    while(i < len/2)
    {
        *temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = *temp;
        i++;
    }
    free(temp);

    return str;

}

char *my_itoa(int num)
{
    int i = 0;
    int len = num_length(num);
    int *arrayNum = number_array(num);
    char *str = malloc(sizeof(char) *len+1);

    while(i != len)
    {
        str[i] = arrayNum[i] + '0';
        i++;
    }
    str[i] = '\0';

    reverse_string(str);

    return str;
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    int i = 0;

    while(str[i] != 0)
    {
        my_putchar(str[i]);
        i++;
    }
}


int blank(char src)
{
    if(src == '\n' || src == '\t' || src == '\v' || src == '\f' || src == '\r' || src == ' ' || src == '\0' || src == ',')
    {
        return 1;
    }
    return 0;
}


int word_counter(char *str)
{
    int i = 0;
    int count = 0;

    while(str[i] != 0)
    {
        if(str[i] != 0 && !blank(str[i]))
        {
            if(str[i] && !blank(str[i]) && blank(str[i+1]))
            {
                count++;
            }
        }
        i++;
    }
    return count;
}

char **split(char *src)
{
    int count_word = word_counter(src);

    char **copy = malloc(sizeof(char*) * count_word +1);
    int i = 0;
    while(*src)
    {
        int j = 0;
        while(*src && blank(*src))
        {
            src++;
        }
        while(*src && !blank(*src)) {
            src++;
            j++;
        }
        copy[i] = malloc(sizeof(char) * j + 1);
        int tmp = j;
        while (j >= 0) {
            copy[i][j] = *src--;
            j--;
        }
        copy[i][tmp] = 0;
        i++;
        src += tmp+1;
    }
    copy[i] = 0;
    return copy;
}

#endif //HANGMAN_HANGMAN_H
