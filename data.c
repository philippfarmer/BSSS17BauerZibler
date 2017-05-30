#include "data.h"
#include <stdio.h>
#include <string.h>


    //Wert hinzuf�gen
    int PUT(char *key, char *value, char *res, data **sm) {
        int i;

        for (i = 0; i < STORELENGTH; i++) {
            if (strcmp(sm[i] -> key, key) == 0) {
                strcpy(res, sm[i] -> value);
                strcpy(sm[i] -> value, value);
                printf("\n--> KEY schon vorhanden und �berschrieben, alte value ist: ");
                return 0;
            }
        }

        for (i = 0; i < STORELENGTH; i++) {
           if (sm[i] -> set == 0) {
                printf("Platz gefunden, Stelle: %i\n", i+1);

                strcpy(sm[i] -> value, value);
                strcpy(sm[i] -> key, key);
                sm[i] -> set = 1;

                return 0;
       }
        }

        printf("Kein freier Platz mehr frei !\n");
        return -1;
    }

    //Wert auslesen
    int GET(char *key, char *res, data **sm) {
        int i;

        for (i = 0; i < STORELENGTH; i++) {
            if (strcmp(sm[i] -> key, key) == 0) {
                strcpy(res, sm[i] -> value);
                //printf("\nValue ist: ");
                return 0;
            }
        }
        printf("\n\nEs wurde kein Wert gefunden\n\n");
        return -1;
    }

    //Wert l�schen
    int DEL(char *key, char* res, data **sm) {
        int i;
        int j;
        for (i = 0; i < STORELENGTH; i++) {
            if (strcmp(sm[i] -> key, key) == 0) {
                strcpy(res, sm[i] -> value);
                strcpy(sm[i] -> value, "");
                strcpy(sm[i] -> key, "");
                sm[i] -> set = 0;

                printf("\nWert gel�scht / Das Array besteht nun aus: \n");

                printf("VALUE ist: %s\n", res);

                return 0;
            }
        }
        printf("\nKey nicht vorhanden ! \n");
        return -1;
    }


    int strtoken(char *str, char *separator, char **token, int size) {
        int i = 0;
        token[0] = strtok(str, separator);
        while (token[i++] && i < size) {
            token[i] = strtok(NULL, separator);
        }
        return (i);
    }
