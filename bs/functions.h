#ifndef BS_FUNCTIONS_H
#define BS_FUNCTIONS_H

#include <stdio.h>
#define STORELENGTH 10

struct key_Value
{
    char *key;
    char *value;
};

struct key_Value key_Value_Store[STORELENGTH];

int put(int key, char *value, char *res);
int get(int key, char *res);
int del(int key, char *res);

#endif //BS_FUNCTIONS_H
