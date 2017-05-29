#include <stdlib.h>
#include "socket.h"

int start()
{
    //Variablen für Socket
    int sock;
    struct sockaddr_in server;      //Socket an diese Adresse gebunden...
    struct sockaddr_in client;      //Socketadresse eines Clients
    //Variablen für Socket Verbindung akzeptieren
    int fileDescriptor;             //FileDescriptor für das Socket
    int client_Len;                 //Länge der Client Daten
    char in[2000];                  //Daten vom Client an den Server
    char out[2000];                 //Daten vom Server an den Client
    client_Len = sizeof(client);    //Größe der Client Nachricht

    //Anlegen eines Sockets
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("creating stream socket");
        exit(2);
    }
    else
    {
        printf("Socket created.\n");
    }

    //SO_REUSEADDR erlaubt anderen Sockets sich zu amselben Port zu verbinden (Obwohl ein Socket verbunden ist)
    /*
    int option = 1;
    setsockopt(sock, SOL_SOCKET,SO_REUSEADDR, &option, sizeof(option));
     */

    //Binden eines Sockets
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4711);

    if(bind(sock, (struct sockaddr *)&server, sizeof(server)<0))
        {
        perror("Error on binding");
    }
    else
    {
        printf("Socket binded.\n");
    }

    //Auf Verbindung hören
    if(listen(sock, 5)<0)
    {
        perror("Erro on listening");
    }
    else
    {
        printf("Listening to server...\n");
    }

    //Verbindung akzeptieren
    while (1)
    {
        fileDescriptor = accept(sock,(struct sockaddr *)&server, &client_Len);
        printf("Connection\n");
        while(read(fileDescriptor, in, 2000) > 0) //Daten vom Array out ==> in
        {
            write(fileDescriptor, out, 2000); //Daten vom Array out ==> Socket
        }
        close(fileDescriptor);  //Der Client hat keine Daten mehr zum übertragen
    }

}