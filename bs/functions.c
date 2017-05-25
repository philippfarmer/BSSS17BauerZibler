#include <stdio.h>
#include <string.h>

#include "functions.h"

int current_length = 0;

int put(char *key, char *value, char *res)
{
    for(int i = 0; i < STORELENGTH; i++)
    {
        if(strcmp(const char *)key_Value_Store.key[i], key)
        {
            res = &key_Value_Store.value[i];
            key_Value_Store.value[i] = value;
            return 0;
        }
    }
    if(current_length == STORELENGTH)
    {
        printf("Nothing can be added\n");
        return -1;
    }
    else
    {
        current_length++;
        strcpy(key_Value_Store.key[current_length],key);
        strcpy(key_Value_Store.value[current_length], value);
        printf("Added Key: %s and Value: %s\n",key_Value_Store.key[i], key_Value_Store.value[i]);
        res = &key_Value_Store.value[current_length];
        return 0;
    }
}

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
}

int del()
{

}
