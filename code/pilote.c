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

#include "Structure.h"

// nom du fifo d'entrée
//const char fifoIN[]="fifoIN";

int main(){

    // ---- Partie de test sur l'écriture dans le FIFO ----

    int efifo,ecriture,pid;
    int efifo2,lecture,ouverture;
    Treponse retour;
    char fifoOut[12];
    //char* fifoIN="fifoIN";

    efifo = open(fifoIN, O_WRONLY);              //On ouvre le fifo en ecriture seulement

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
            printf("\n\n ---------------------------------------------\n");

         }
    }

    close (efifo);

    // On genère le nom du fifo Out

    char spid[4];
    sprintf(spid,"%d",pid);

    strcpy(fifoOut,"fifo");
    strcat(fifoOut,spid);


    // Creation du FIFO de sortie

    efifo2=mkfifo(fifoOut,0666);

	if(efifo2 < 0) {                        //si mkfifo ne fonctionne pas

		if(efifo2 == -1) {             //utilise la valeur d'erreurs de mkfifo
			printf("\n Le FIFO existait déjà, il a été réinitialisé !");
			unlink(fifoOut);                //suprime le nom du fifo déja existant
			mkfifo(fifoOut, 0666);
		}
		else {
			printf("\n Probleme lors de la creation du %s.\n",fifoIN);
			printf("\n Erreur errno numéro : %d\n", efifo); //renvoie le numéro d'erreur du systeme
			printf("\n Le système va s'arretter !");
			exit(-1);                       //on force la fin du programme car sans fifo sa peut pas fonctionner
    	}
	}
	else{

        printf("\n\n Le FIFO a été créé avec succès : %s",fifoOut);
        printf("\n ---------------------------------------------");
	}

    ouverture = open(fifoOut, O_RDONLY); // Ouverture en lecture

    if(ouverture < 0){
        printf("\n Erreur lors de l'ouverture du FIFO Out");
        printf("\n Erreur : %d\n",ouverture);
        exit(-1);
    }
    else {
        lecture=read(ouverture,&retour,sizeof(Treponse));
        if(lecture < 0){
        printf("\n\n Erreur lors de la lecture dans le fifo");
        printf("\n Erreur %d\n",lecture);
        exit(-1);
  	}
  	else {
        printf("\n\n Reponse du serveur :");
        printf("\n --------------------");
  	    printf("\n\n Reponse du serveur pour : %d\n",retour.pid);
  	    printf("\n Temps : %s\n",retour.reponse);
  	}
    }

    close(ouverture);

}
