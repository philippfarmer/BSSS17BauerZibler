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
            res = key_Value_Store.value[i];
            key_Value_Store.value[i] = value;
            return 0;
        }
    }
    if(current_length == STORELENGTH)
    {

    }
}

int get()
{

}

int del()
{

}
