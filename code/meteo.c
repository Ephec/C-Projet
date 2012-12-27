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
#include <time.h>

#include "Structure.h"

int main(){

    int ouverture, ecriture;
    char ATIS[10][100];
    int i, nbInfo;

    nbInfo=4;
    system("clear");

    printf("\n\n Programme de gestion des informations ATIS");
    printf("\n ------------------------------------------");

    strcpy(ATIS[0],"EBBR 0615 20015KT 8000 RA SCT010 OVC015 TEMPO 0608 5000 RA BKN005 BECMG 0810 9999 NSW BKN025");
    strcpy(ATIS[1],"EBBR 0712 15020KT 6200 FG SCT010 OVC015 TEMPO 1450 6000 RA BKN005 BECMG 0810 5000 NSW BKN025");
    strcpy(ATIS[2],"EBBR 0620 20015KT 8000 SA SCT010 OVC015 TEMPO 0780 4000 RA BKN005 BECMG 0810 4000 NSW BKN025");
    strcpy(ATIS[3],"EBBR 0607 20015KT 8000 RA SCT010 OVC015 TEMPO 0608 3000 RA BKN005 BECMG 0810 9999 NSW BKN025");


     for(i=0;i<nbInfo;i++){

        printf("\n\n Message actuel :");
        printf("\n\n %s",ATIS[i]);
        printf("\n");
        ouverture=open(meteo, O_WRONLY);
        if(ouverture>0){
            ecriture=write(ouverture,ATIS[i],sizeof(ATIS[0]));
        }
        close(ouverture);
        if(i==nbInfo-1) i=-1;
        sleep(60);

     }

    return 0;

}
