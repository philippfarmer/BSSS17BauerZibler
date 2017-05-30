#ifndef BS_FUNCTIONS_H
#define BS_FUNCTIONS_H

#include <stdio.h>
#define STORELENGTH 1024

/*struct kv
{
    char *key;
    char *value;
};*/

//struct kv kvs[STORELENGTH];
//kvs[STORELENGTH].key = {0};
//kvs[STORELENGTH].value = {0};

char *key[STORELENGTH];// = {0};
char *value[STORELENGTH];// = {0};

int put(char *key, char *value, char *res);
int get(char *key, char *res);
int del(char *key, char *res);
extern int strtoken(char *str, char *separator, char **token, int size);

#endif //BS_FUNCTIONS_H
