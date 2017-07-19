#ifndef DATA_H_
#define DATA_H_

#include <stdlib.h>
#include <sys/types.h> //data types

#define STORELENGTH 32
#define N 1024

typedef struct data{
    char key[STORELENGTH];
    char value[STORELENGTH];
}Data;

int PUT(char* key, char* value, char* res, Data *sm);

int GET(char* key, char* res, Data *sm);

int DEL(char* key, Data *sm);

int strtoken(char *str, char *separator, char **token, int size);

#endif