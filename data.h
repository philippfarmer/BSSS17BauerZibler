#ifndef DATA_H_
#define DATA_H_

#include <stdlib.h>
#include <sys/types.h> //data types

#define STORELENGTH 5

typedef struct{
    char key[20];
    char value[20];
    int set;
}data;

int PUT(char* key, char* value, char* res, data **sm);

int GET(char* key, char* res, data **sm);

int DEL(char* key, char* res, data **sm);

int strtoken(char *str, char *separator, char **token, int size);

#endif
