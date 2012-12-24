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

    int lecture, pidLu, lfifo;

    lfifo = open("fifoIN",O_RDONLY);
	if (lfifo < 0){                     //Si problème de l'ouverture
  		printf("Erreur lors de l'ouverture du FIFO\n");
  		printf("Erreur : %d\n",lfifo);
		exit(-1);
  	}

  	lecture=read(lfifo,&pidLu,sizeof(int));

  	if(lecture < 0){
        printf(" Erreur lors de la lecture dans le fifo");
        printf("\n Erreur %d",lecture);
        exit(-1);
  	}
  	else {
  	    printf("Lecture PID : %d",pidLu);
  	}

  	close(lfifo);

}
