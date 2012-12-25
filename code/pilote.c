#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  //Pour mkFifo
#include <sys/stat.h>
#include <errno.h>      //Pour les erreur
#include <unistd.h>     //Pour read
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <fcntl.h>

// nom du fifo d'entrée
//const char fifoIN[]="fifoIN";

int main(){

    // ---- Partie de test sur l'écriture dans le FIFO ----

    int efifo,ecriture,pid;
    //char* fifoIN="fifoIN";

    efifo = open("fifoIN", O_WRONLY);              //On ouvre le fifo en ecriture seulement

    if(efifo < 0){
        printf("\nErreur lors de l'ouverture du fifoE");
        printf("\nerrno: %d\n",efifo);
        exit(-1);
    }
    else {
        pid=getpid();
        ecriture = write(efifo, &pid, sizeof(int));      //On ecrit toutes les données dans le fifo
        if (ecriture > 0) {
            printf("\n Demande au serveur :");
            printf("\n --------------------\n\n");
            printf(" PID du processus : %d",pid);
            printf("\n\n ---------------------------------------------\n\n");

         }
    }

    close (efifo);

}
