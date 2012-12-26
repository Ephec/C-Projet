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

void creerFifoEntree();
void ouvrirFifoIn(int *ouverture);
void traitement(int ouverture);

int main(){

    int ouvertureIn;

    creerFifoEntree();

        ouvrirFifoIn(&ouvertureIn);
        traitement(ouvertureIn);
        close(ouvertureIn);

	return(0);
}

void creerFifoEntree(){

	int efifo;

	printf("\n\n Serveur ATIS");
	printf("\n ------------");
	printf("\n\n => FIFO d'entrée des demandes ATIS : /%s",fifoIN);

	printf("\n\n Etat du FIFO :");
	printf("\n --------------");

	// création du fifo, e pour erreur dans efifo
	efifo=mkfifo(fifoIN,0666);

	if(efifo < 0) {                        //si mkfifo ne fonctionne pas

		if(efifo == -1) {             //utilise la valeur d'erreurs de mkfifo
			printf("\n\n Le FIFO existait déjà, il a été réinitialisé !");
			unlink(fifoIN);                //suprime le nom du fifo déja existant
			mkfifo(fifoIN, 0666);
		}
		else {
			printf("\n\n Probleme lors de la creation du %s.\n",fifoIN);
			printf("\n Erreur errno numéro : %d\n", efifo); //renvoie le numéro d'erreur du systeme
			printf("\n Le système va s'arretter !");
			sleep(3);
			exit(-1);                       //on force la fin du programme car sans fifo sa peut pas fonctionner
    	}
	}
	else{

        printf("\n\n Le FIFO a été créé avec succès");

	}

}

void ouvrirFifoIn(int *ouverture){

    *ouverture=open(fifoIN, O_RDONLY);
	if(*ouverture==-1)
	{
		perror("\n Echec ouverture du FIFO");
		exit(1);
	}
	else {

        printf("\n FIFO IN ouvert en lecture");

	}
}

void traitement(int ouverture){

    int pid,lecture;
    int ouvertureOut, ecriture, efifo;
    int i,compteur;
    char fifoOut[12];
    Treponse retour;

    printf("\n\n Etat des demands ATIS :");
	printf("\n -----------------------");
	compteur=0;

    for(i=0;i<2;i++){

	lecture=read(ouverture,&pid,sizeof(int));

	if(pid!=retour.pid){

	    compteur=0;

        if(lecture < 0){
            printf("\n\n Erreur lors de la lecture dans le fifo");
            printf("\n Erreur %d",lecture);
            exit(-1);
        }
        else {
            printf("\n\n Lecture PID (voir pilote) : %d",pid);
        }

        // On genère le nom du fifo Out

        char spid[4];
        sprintf(spid,"%d",pid);

        strcpy(fifoOut,"fifo");
        strcat(fifoOut,spid);

        // Ouverture du fifo de sortie du client

        printf("\n\n Reponse au pilote :");
        printf("\n -------------------");

        sleep(3);

        ouvertureOut=open(fifoOut, O_WRONLY);
        if(ouvertureOut==-1)
        {
            perror("\n Echec ouverture du FIFO Out");
            exit(1);
        }
        else {

            printf("\n\n FIFO Out ouvert en écriture : %s",fifoOut);

        }

        retour.pid=pid;
        strcpy(retour.reponse,"OK - Temps dégagé et vent de 20 km/h");

        printf("\n PID : %d",retour.pid);
        printf("\n Temps : %s",retour.reponse);
        printf("\n\n -------------------------------------------");

        ecriture = write(ouvertureOut, &retour, sizeof(Treponse));

        close(ouvertureOut);

	}
	else{
        printf("\n Attente d'une demande pendant 10 secondes...\n");
        sleep(10);
        compteur++;
        if(compteur>5){

            printf("\n\n Le serveur a attendu trop longtemps (60 secondes)!");
            printf("\n Il va quitter...");
            i=2;

        }
	}

    i--;

    } // fin du for
}
