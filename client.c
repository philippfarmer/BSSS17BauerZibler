#include <stdio.h>
#include <sring.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

void bzero (void *to, size_t count) {
    memset (to,0,count);
}

int main() {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not create socket");
        exit(1);
    }
    puts("CLient-Socket erstellt");

    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //localhost
    server.sin_family = AF_INET;
    server.sin_port = htons(6789);

    //Mit derm Server verbinden

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return -1;
    }

    puts("Connected\n");

    while(1) {
        bzero(message, 1000);
        bzero(server_reply, 2000);

        printf("Was soll passieren");

        fgets(message, 1000, stdin);

        /*Zum Senden von Daten von einem Socket an den Stream wird gewöhnlich die Funktion send() verwendet
        (bei TCP, UDP benutzt sendto) als parameter sind der fd, pointer auf die daten die länge und ein int für flags*/

        if ( send(sock, message, strlen(message), 0) < 0) {
            printf("Senden der Daten fehlgeschlagen");
            return 1;
        }

        /*Antwort erhalten*/
        /*Um Daten von einem Stream-Socket zu empfangen (zu lesen), wird die Funktion recv() verwendet.
        ssize_t recv ( int socketfd, void *data , size_t data_len, unsigned int flags );*/

        if( recv(sock, server_reply, 2000, 0) < 0) {
            printf("Empfangen fehlgeschlagen");
            break;
        }

        printf("%s", server_reply);
        fflush(0);
    }

    close(sock);
    return 0;
}