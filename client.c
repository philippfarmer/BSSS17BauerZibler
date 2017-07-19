#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>


void bzero (void *to, size_t count){
    memset (to, 0, count);
}


int main()
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        perror("Could not create socket");
        exit(1);
    }
    puts("Client-Socket erstellt");

    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //localhost
    server.sin_family = AF_INET;
    server.sin_port = htons( 6969 );

    /*Mit dem Server verbinden*/
    /*Nachdem mit den Sockets die Kommunikationsendpunkte erzeugt wurden, kann der Client nun versuchen,
    eine Verbindung zum Server-Socket herzustellen.
    Dies wird mit der Funktion connect() versucht
    int connect (int socket, const struct sockaddr *addr, int addrlen);
    */
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    /*Mit dem Server kommunizieren*/
    while(1)
    {
        bzero(message, 1000);
        bzero(server_reply, 2000);
        printf("Was soll getan werden : ");
        /*Nachricht in string einlesen*/
        /*scanf("%s" , message);*/
        fgets(message, 1000, stdin);

        /*Befehle senden*/
        /*Zum Senden von Daten von einem Socket an den Stream wird gewöhnlich die Funktion send() verwendet
        (bei TCP, UDP benutzt sendto) als parameter sind der fd, pointer auf die daten die länge und ein int für flags*/

        if( send(sock , message , strlen(message) , 0) < 0)
        {
            printf("Senden der Daten fehlgeschlagen");
            return 1;
        }

        /*Antwort erhalten*/
        /*Um Daten von einem Stream-Socket zu empfangen (zu lesen), wird die Funktion recv() verwendet.
        ssize_t recv ( int socketfd, void *data , size_t data_len, unsigned int flags );*/

        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            printf("Empfangen der Daten fehlgeschlagen");
            break;
        }

        printf("%s", server_reply);
        fflush(0);
        //bzero(message, 1000);
        //bzero(server_reply, 2000);
    }

    close(sock);
    return 0;
}
/*puts in printfs ändern vlt wird die ausgabe dann ordentlicher*/