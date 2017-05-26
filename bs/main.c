#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {

    int sock;                       // das Socket
    struct sockaddr_in server;      // Socketadresse des Servers
    struct sockaddr_in client;      // Socketadresse eines Clients
    int fileDescriptor;             // Filedeskriptor für das Socket
    int client_len;                 // Länge der ClientD-Daten
    char in[2000];                  // Daten vom Client an den Server
    char out[2000];                 // Daten vom Server an den Client
    client_len = sizeof(client);    // Größe der Client-Nachricht

    /* Anlegen eines Sockers */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("creating stream socket");
        exit(1);
    }

    /* Binden einer Adresse an das Socket */
    server.sin_familiy = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4994);

    bind(sock, (struct sockaddr *) &server, sizeof(server));

    /* Auf Verbindung hören */
    listen(sock, 5);

    /* Verbindung akzeptieren */
    fileDescriptor = accept(sock, &client, &client_len);

    while (1) { // Server wartet auf Anfrage
        fileDescriptor = accept(sock, &client, &client_len);
        while (read(fileDescriptor, in, 2000) > 0) { // Daten vom Socket ==> in
            // Hier wird nun mit den Daten des Clients gearbeitet.
            if(strcmp(token[0], "PUT") == 0){
                var = put(token[1], token[2], res);
                puts("PUT funktioniert\n");
            } else if (strcmp(token[0], "GET") == 0){
                var = get(token[1], res);
                puts("GET funktioniert\n");
            } else if (strcmp (token[0], "DEL") == 0){
                var = del(token[1], res);
                puts("DEL funktioniert\n");
            } else {
                puts("Ungültige Eingabe vom Client\n");
            }
            write(fileDescriptor, out, strlen(out));// Daten vom Array out ==> Socket
        }
        close(fileDescriptor); // Der Client hat keine Daten mehr zu übertragen.
    }

}