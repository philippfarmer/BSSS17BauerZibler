#include <stdio.h>
#include <string.h>

#include "functions.h"


//int current_length = 0;
int a;

int put(char *key, char *value, char *res)
{
    for(a = 0; a < STORELENGTH; a++)
    {

        /*if(current_length == STORELENGTH)

        {
            strcpy(res, "Es können keine Daten hinzugefügt werden!");
            printf("\nEs können keine Daten hinzugefügt werden!");
            return -1;
        }

        else*/ if(strcmp(key[a], key) == 0)
        {
            strcpy(key[a], key);
            strcpy(value[a], value);
            printf("\nValue wurde ersetzt.");
            return 0;
        }
        else if(key[a] == 0) // NULL macht probleme
        {
            strcpy(key[a], key);
            strcpy(value[a], value);
            strcpy(res, value);
            //current_length++;
            printf("Key: %s und Value: %s", key[a], value[a]);
            return 0;
        }
        else if(strcmp(key_Value_Store.key[a], NULL) == 0)
        {
            strcpy(key_Value_Store.key[a],key);
            strcpy(key_Value_Store.value[a],value);
            strcpy(res, value);
            //current_length++;
            printf("Key: %s und Value: %s", key[a], value[a]);
            return 0;
        }
    }
}

/*int get(char *key, char *res)
{
    if(current_length == 0)
    {
        printf("Es sind kein Daten gespeichert.\n");
        return -1;
    }
    else
    {
        for(a = 0; a < STORELENGTH; a++)
        {
            if(strcmp(key_Value_Store.key[a], key)==0)
            {
                strcpy(res, key_Value_Store.value[a]);
                return 0;
            }

        }
    }
    strcpy(res, "Wert nicht gefunden!");
    printf("Wert nicht gefunden\n");
    return -1;
}*/

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
