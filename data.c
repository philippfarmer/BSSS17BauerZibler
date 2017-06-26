#include "data.h"
#include <stdio.h>
#include <string.h>

int length = 0;

    //Put fnktion wird benutzt um Werte einzufügen
    int PUT(char *key, char *value, char *res, data **sm) {
        int i;
        
        //Check ob eine Position schon belegt ist
        for (i = 0; i < STORELENGTH; i++) {
            if (strcmp(sm[i] -> key, key) == 0) {
                strcpy(res, sm[i] -> value);
                strcpy(sm[i] -> value, value);
                printf("\n--> KEY schon vorhanden und ueberschrieben, alte value ist: ");
                return 0;
            }
        }

        if(length < STORELENGTH) {
            printf("Platz gefunden, Stelle: %i\n", length);
            strcpy(sm[length] -> value, value);
            strcpy(sm[length] -> key, key);
            length++;

            return 0;
        }
    }

    //Wert auslesen
    int GET(char *key, char *res, data **sm) {
        int i;

        for (i = 0; i < STORELENGTH; i++) {
            if (strcmp(sm[i] -> key, key) == 0) {
                strcpy(res, sm[i] -> value);
                printf("\nValue ist: ");
                return 0;
            }
        }
        printf("\n\nEs wurde kein Wert gefunden\n\n");
        return -1;
    }

    //Wert loeschen
    int DEL(char *key, data **sm) {
        int i;
        int j;
        for (i = 0; i < STORELENGTH; i++) {
            if (strcmp(sm[i] -> key, key) == 0) {
                strcpy(sm[i] -> value, "");
                strcpy(sm[i] -> key, "");
                sm[i] -> set = 0;

                printf("Wert geloescht / Das Array besteht nun aus: \n");

                for (j = 0; j <  STORELENGTH; j++) {
                    printf("%i KEY ist: %s\n", j+1, sm[j] -> key);
                    printf("%i VALUE ist: %s\n", j+1, sm[j] -> value);
                }

                return 0;
            }
        }
        printf("\nKey nicht vorhanden ! \n");
        return -1;
    }


    int strtoken(char *str, char *separator, char **token, int size) {
        int i = 0;
        token[0] = strtok(str, separator);
        while (token[i++] && i < size)
            token[i] = strtok(NULL, separator);
        return (i);
    }