#ifndef BS_FUNCTIONS_H
#define BS_FUNCTIONS_H

#include <stdio.h>
#define STORELENGTH 1024

struct key_Value
{
    char *key[STORELENGTH];
    char *value[STORELENGTH];
};

struct key_Value key_Value_Store;

int put(int key, char *value, char *res);
int get(int key, char *res);
int del(int key, char *res);

#endif //BS_FUNCTIONS_H
