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

const char fifoIN[]="./fifoIN.fifo";

int main()
{
	int efifo, descFifo;

	// création du fifo, e pour erreur dans efifo
	efifo=mkfifo(fifoIN,0666);

	if(efifo < 0) {                        //si mkfifo ne fonctionne pas
		if(efifo == -1) {             //utilise la valeur d'erreurs de mkfifo
			printf("Le %s existait déja, réinitialisation....\n",fifoIN);
			unlink(fifoIN);                //suprime le nom du fifo déja existant
			mkfifo(fifoIN, 0666);
		}
		else {
			printf("Probleme lors de la creation du %s.\n",fifoIN);
			printf("Erreur errno numéro : %d\n", efifo); //renvoie le numéro d'erreur du systeme
			exit(-1);                       //on force la fin du programme car sans fifo sa peut pas fonctionner
    	}
	}


	// ouverture du tube
	descFifo=open(fifoIN, O_RDONLY);
	if(descFifo==-1)
	{
		perror("echec ouverture tube");
		exit(1);
	}

	close(descFifo);
}
