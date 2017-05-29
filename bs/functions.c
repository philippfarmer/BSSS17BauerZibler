#include <stdio.h>
#include <string.h>

#include "functions.h"

int current_length = 0;
int a;

int put(char *key, char *value, char *res)
{
    for(a = 0; a < STORELENGTH; a++)
    {
        if(current_length == STORELENGTH)
        {
            strcpy(res, "Es können keine Daten hinzugefügt werden!");
            printf("\nEs können keine Daten hinzugefügt werden!");
            return -1;
        }
        else if(strcmp(key_Value_Store.key[a], key) == 0)
        {
            strcpy(key_Value_Store.key[a], key);
            strcpy(key_Value_Store.value[a], value);
            printf("\nValue wurde ersetzt.");
            return 0;
        }
        else if(strcmp(key_Value_Store.key[a], NULL) == 0)
        {
            strcpy(key_Value_Store.key[a],key);
            strcpy(key_Value_Store.value[a],value);
            strcpy(res, value);
            current_length++;
            printf("Key: %s und Value: %s", key_Value_Store.key[a], key_Value_Store.value[a]);
            return 0;
        }
    }
}

int strtoken(char *str,char *separator, char **token, int size)
{
    int i = 0;
    token[0] = strtok(str,separator);
    while(token[i++] && i < size)
    {
        token[i] = strtok(NULL, separator);
    }
    return (i);
}

/*
int get(char *key, char *res)
{
    if(current_length == 0)
    {
        printf("There are no files are safed!\n");
        return -1;
    }
    else
    {
        for(i = 0; i < STORELENGTH; i++)
        {
            if(strcmp((const char *)key_Value_Store.key[i], key) == 0)
            {
                printf("Key: %s \n Value: %s",key_Value_Store.key[i], key_Value_Store.value[i]);
                res = &key_Value_Store.value[i];
                return 0;
            }
            else
            {
                printf("No Value found!\n");
                return -1;
            }
        }
    }
}*/


/*int del(char *key, char *res)
{
    if(current_length == 0)
    {
        strcpy(res, "Es sind keine Daten vorhanden!");
        printf("Keine Daten vorhanden");
        return -1;
    }
    else
    {
        for(a = 0; a < STORELENGTH; a++)
        {
            if(strncmp(key_Value_Store[a].key, key, 1)==0)
            {
                strcpy(res, key_Value_Store[a].value);
                strcpy(key_Value_Store[a].key, NULL);
                strcpy(key_Value_Store[a].value, NULL);
                return 0;
            }
        }
    }
    strcpy(res, "Keinen passenden Wert gefunden!");
    printf("Nichts gefunden");
    return -1;
}*/