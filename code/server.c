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

const char fifoIN[]="fifoIN";

void creerFifoEntree();
void traitement();

int main(){

    creerFifoEntree();
    traitement();

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

void traitement(){

    int ouverture, lecture, pid;

	// ouverture du tube
	ouverture=open(fifoIN, O_RDONLY);
	if(ouverture==-1)
	{
		perror("\n Echec ouverture du FIFO");
		exit(1);
	}
	else {

        printf("\n FIFO ouvert en lecture");

	}

	printf("\n\n Etat des demands ATIS :");
	printf("\n\n -----------------------");

	lecture=read(ouverture,&pid,sizeof(int));

  	if(lecture < 0){
        printf("\n\n Erreur lors de la lecture dans le fifo");
        printf("\n Erreur %d",lecture);
        exit(-1);
  	}
  	else {
  	    printf("\n\n Lecture PID (voir pilote) : %d",pid);
  	}

	close(ouverture);

}
