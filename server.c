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
#include <sys/sem.h>

int sock, fd, read_size, id;    //Socket , FileDescriptor
socklen_t client_len;
struct sockaddr_in server, client;
char in[2000], out[2000];
char res[32];
char *temp = &res; //pointer auf res string
char del[] = " ";
int i, j, y, semID, semaID, sharedcounterID, *sharedcounter;
struct sembuf up, down, upa, downa;
unsigned short signals[1];
char *tok[3];
int pid;       //Process Identification (Eindeutige Nummer für den Prozess)

data *sm[STORELENGTH];

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

/*---------Persistenz Funktionen---------*/

int readCache (Data *sm){
    FILE *ptr;

    ptr = fopen("servercache.bin","rb");  // r for read, b for binary
    if(ptr != NULL){
        fread(sm,sizeof(Data) *N,1,ptr); // Daten auslesen
        fclose(ptr);
    }
    return 0;
}

int saveCache (Data *sm){
    FILE *write_ptr;
    write_ptr = fopen("servercache.bin","wb");  // w for write, b for binary
    if(write_ptr != NULL){
        fwrite(sm,sizeof(Data) *N,1,write_ptr); // write 10 bytes from our buffer
        fclose(write_ptr);
    }
    return 0;
}
void intHandler(int sig){

    saveCache(sm);

    shmctl(id, IPC_RMID, NULL);

    shmctl(sharedcounterID, IPC_RMID, NULL);

    semctl(semID, 1, IPC_RMID, 0);
    semctl(semacounter , 1, IPC_RMID, 0);

    printf("Saved and Exit");
    fflush(0);
    exit(0);
}

int main(int argc, char *argv[]) {

    signal(SIGINT, intHandler);
    signal(SIGTERM, intHandler);


    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("creating stream socket");
        exit(2);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(6789); //Convert multi-byte integer types from host byte order to network byte order

    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind socket to server_addr");
        exit(1);
    }

    if (listen(sock, 5) < 0) {
        perror("listening for connections");
    }

    client_len = sizeof(client);

    id = shmget(IPC_PRIVATE,sizeof(data),IPC_CREAT|0777);/* id = shmget(key, size, flag)
                                                        id = Integer der als ID des Segments verwendet wird
                                                        key = Numerischer Schlüssel long für das Segment IPC_PRIVATE lässt den Kern ihn selbst festlegen
                                                        size = Größe des Segments in Bytes Int
                                                        flag = typ int 0777 bietet uneingeschränkten Zugriff
                                                        */
    sharedcounterID = shmget(IPC_PRIVATE, 1000, IPC_CREAT | 0777);

    sharedcounter = (int *)shmat(sharedcounterID,0,0);
    *sharedcounter = 0;

    if (id < 0){
      printf ("Fehler bei key %d, mit der size %d\n", IPC_PRIVATE, SEGSIZE);
    }

    for (y = 0; y < STORELENGTH; y++){
      sm[y] = (data *) shmat(id,NULL,0);
      sm[y] -> set = 0;
    }

    /*------------------Semaphore------------------*/
    /* id=semget(key, nsems, flag) legt neue Semaphorengruppen an oder greift auf
    bestehende zu. "id" ist ein Integer der zur Identifizierung der Semaphore dient.
    "key" ist der Schlüssel vom Typ long, für die Gruppe. "nsems" gibt die Anzahl der Semaphoren der
    Gruppe an (als int). "flag" ist ein int, welcher die Zugriffsmöglichkeiten festlegt. */

    semID = semget(IPC_PRIVATE, 1, IPC_CREAT | 0777);

    signals[0] = 1;
    semctl(semID, 0, SETALL, signals);

    down.sem_num = 0;           //Nummer der Semaphore innerhalb der Gruppe
    down.sem_op = -1;           //legt operation fest (Wert > 0 = UP-, Wert < 0 = DOWN-Operation)
    down.sem_flg = SEM_UNDO;    //Flags zur Steuerung angebbar

    up.sem_num = 0;
    up.sem_op = 1;
    up.sem_flg = SEM_UNDO;

    semaID = semget(IPC_PRIVATE, 1, IPC_CREAT | 0777);

    signals[0] = 1;

    semctl(semaID, 0, SETALL, signals);
    downa.sem_num = 0;
    downa.sem_op =-1;
    downa.sem_flg = SEM_UNDO;

    upa.sem_num = 0;
    upa.sem_op = 1;
    upa.sem_flg = SEM_UNDO;


    readCache(sm);

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

                    semop(semID, &down, 1);
                    printf("Befehl: %s\n", tok[0]);
                    printf("Key: %s\n", tok[1]);
                    printf("Value: %s\n", tok[2]);

                    PUT(tok[1], tok[2], temp, sm); // referenz auf erste element

                    semop(semID, &up, 1);

                }else if(strcmp(tok[0], "get") == 0){
                    semop(semaID, &downa, 1);       //Sema Block
                    *sharedcounter += 1;            //Readcouner erhöht

                    printf("\nLese Anfrage gestartet, aktuell %d", *sharedcounter);

                    if(*sharedcounter == 1){        //überprüfung ob get angefragt wurde
                        semop(semID, &down, 1);     //Sem wird geblockt
                        printf("\nPut geblockt");
                    }
                    semop(semaID,&upa, 1);          //Sema wird freigegeben
                    sleep(10);

                    GET(tok[1], temp, sm);          //get wird ausgeführt

                    semop(semaID, &downa, 1);       //sema wird geblockt

                    *sharedcounter -= 1;            //readcounter wird verringert
                    printf("Akuelle get anfragen %d", *sharedcounter);
                    if(*sharedcounter == 0){        //Wenn keine anfrage läuft
                        semop(semID, &up, 1);       //sem wird freigegeben
                        printf("\nLese Prozesse beendet, put freigegeben");
                    }
                    semop(semaID, &upa, 1);         //Sema wird freigegeben

                } else if(strcmp(tok[0], "del") == 0){
                    semop(semID, &down, 1);         //Sem wird geblockt
                    DEL(tok[1], sm);
                    semop(semID, &up, 1);           //Sem wird freigegeben
                } else if(strcmp(tok[0], "close") == 0){
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
