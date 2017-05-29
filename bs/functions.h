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

int put(char *key, char *value, char *res);
int get(char *key, char *res);
int del(char *key, char *res);
extern int strtoken(char *str, char *separator, char **token, int size);

#endif //BS_FUNCTIONS_H
