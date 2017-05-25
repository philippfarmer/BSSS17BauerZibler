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

int get()
{

}

int del()
{

}
