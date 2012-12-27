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

	printf("\n\n Attente du premier client pour initialiser le FIFO...");

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

        printf("\n Le FIFO a été créé avec succès");

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
    int openMeteo, lecMeteo;
    char fifoOut[12];
    Tdemande demande;
    Treponse retour;

    printf("\n\n Etat des demands ATIS :");
	printf("\n -----------------------");
	compteur=0;

    for(i=0;i<2;i++){

	lecture=read(ouverture,&demande,sizeof(demande));
	if(lecture>0){

	    compteur=0;

        if(strcmp(demande.type,"ASK")==0){

            if(lecture < 0){
                printf("\n\n Erreur lors de la lecture dans le fifo");
                printf("\n Erreur %d",lecture);
                exit(-1);
            }
            else {
                printf("\n\n Lecture PID (voir pilote) : %d",demande.pid);
                printf("\n Type de demande : %s",demande.type);
            }

            // On genère le nom du fifo Out

            char spid[4];
            sprintf(spid,"%d",demande.pid);

            strcpy(fifoOut,"fifo");
            strcat(fifoOut,spid);

            // Ouverture du fifo de sortie du client

            printf("\n\n Reponse au pilote :");
            printf("\n -------------------");
            printf("\n");
            sleep(5);

            ouvertureOut=open(fifoOut, O_WRONLY);
            if(ouvertureOut==-1)
            {
                perror(" Echec ouverture du FIFO Out");
                exit(1);
            }
            else {

                printf("\n FIFO Out ouvert en écriture : %s",fifoOut);

            }

            retour.pid=demande.pid;
            //strcpy(retour.reponse,"OK - Temps dégagé et vent de 20 km/h");

            openMeteo=open(meteo, O_RDONLY);
            if(openMeteo>0){

                lecMeteo=read(openMeteo,(retour.reponse),sizeof(retour.reponse));

            }

            printf("\n PID : %d",retour.pid);
            printf("\n Temps : \n %s",retour.reponse);
            printf("\n\n -------------------------------------------\n");

            ecriture = write(ouvertureOut, &retour, sizeof(Treponse));

            close(ouvertureOut);

        }

        if(strcmp(demande.type,"OK")==0){
            printf("\n Accusé de réception :");
            printf("\n PID : %d",demande.pid);
            //printf("\n Appuyer sur une touche pour continuer");
            //char temp[10];
            //fgets(temp, 10, stdin);

            char spid[4];
            sprintf(spid,"%d",demande.pid);

            strcpy(fifoOut,"fifo");
            strcat(fifoOut,spid);
            printf("\n Fermeture & suppression du FIFO de sortie : %s",fifoOut);
            printf("\n");

            unlink(fifoOut);
            sleep(2);

        } // fin du if pour OK


        if(strcmp(demande.type,"KO")==0){

            printf("\n PID : %d",demande.pid);
            printf("\n Erreur lors de la reception des informations");
            printf("\n Une nouvelle demande a été envoyée par le pilote\n");
            sleep(2);

        } // fin du if pour KO

	} // fin du if fifo contient qqch
	else{

            if(compteur==1){
                printf("\n Toutes les demandes ont été traitées pour le moment...");
                printf("\n Attente de nouvelle(s) demande(s)...");
                printf("\n");
            }
            sleep(1);
            compteur++;
            if(compteur>300){

                printf("\n Le serveur a été inactif pendant 60 secondes! Il ne traite plus aucune demande !");
                printf("\n Pour le réactiver, appuyer sur une touche...");
                char temp[10];
                fgets(temp, 10, stdin);

            }
        } // fin du if pour la demande

    i--;

    } // fin du for
}

void liremeteo(char temp[100]){

    int ouverture,lecture;
    char atis[100];

    ouverture=open(meteo, O_RDONLY);
    if(ouverture>0){

        lecture=read(ouverture,atis,sizeof(atis));

    }

    strcpy(atis,temp);

}
