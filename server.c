#include "data.h"
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h> //definitions for internet operations
#include <netinet/in.h> //Internet address family
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>




void bzero (void *to, size_t count){
    memset (to, 0, count);
}
void doprocessing (int sock) {
   int n;
   char buffer[256];
   bzero(buffer,256);
   n = read(sock,buffer,255);

   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }

   printf("Here is the message: %s\n",buffer);
   n = write(sock,"I got your message",18);

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }

}

int main(int argc, char *argv[]) {
    int sock, fd, read_size, id;
    socklen_t client_len;
    struct sockaddr_in server, client;
    char in[2000], out[2000];
    char res[32];
    char *temp = &res; //pointer auf res string
    char del[] = " ";
    int i, j, y;



    data *sm[STORELENGTH];



    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("creating stream socket");
        exit(2);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2905); //Convert multi-byte integer types from host byte order to network byte order

    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind socket to server_addr");
        exit(1);
    }

  //  sm();

    if (listen(sock, 5) < 0) {
        perror("listening for connections");
    }

    client_len = sizeof(client);

    char *tok[3];
    int pid;
    id= shmget(IPC_PRIVATE,sizeof(data),IPC_CREAT|0777);

    if (id < 0){
      printf ("Fehler bei key %d, mit der size %d\n", IPC_PRIVATE, SEGSIZE);
    }

    for (y = 0; y < STORELENGTH; y++){
      sm[y] = (data *) shmat(id,NULL,0);
      sm[y] -> set = 0;
    }

    while (1) {
        fd = accept(sock, (struct sockaddr*)&client, &client_len);
        pid = fork();
        if(pid < 0) {
         perror("ERROR on fork");
         exit(1);
       }
          if (pid == 0) {
         /* This is the client process */
          close(sock);
          while ((read_size = recv(fd, in, 2000, 0)) > 0) {
              strtoken(in, del, tok, 3);

              printf("\n==================================\n");

              if(strcmp(tok[0], "put") == 0){

                  printf("Befehl: %s\n", tok[0]);
                  printf("Key: %s\n", tok[1]);
                  printf("Value: %s\n", tok[2]);

                  PUT(tok[1], tok[2], temp, sm); // referenz auf erste element

              }else if(strcmp(tok[0], "get") == 0){
                  GET(tok[1], temp, sm);

              }else if(strcmp(tok[0], "del") == 0){
                  DEL(tok[1], temp, sm);

              }else if(strcmp(tok[0], "close") == 0){
                  shutdown(fd, 2);
              } else{
                  printf("\nFalsche Eingabe !\n");
              }


              bzero(in, sizeof(in)); //in auf 0 setzen
              strcpy(out, res); //res in out
              bzero(res, sizeof(res)); //res auf 0 setzen
              write(fd, out, strlen(out)); //out ausgeben
              bzero(out, sizeof(out)); //out auf 0 setzen

          }

          close(fd);


          exit(0);
        }
        else {
         close(fd);
       }


}
}
