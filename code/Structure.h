#define fifoIN "fifoIN"
#define meteo "meteo.txt"

// Une demande au serveur composé du PID et d'un type
// Le type peut être ASK, OK ou KO
typedef struct{

    int pid;
    char type[3];

} Tdemande;

// Une réponse avec le PID (pour être certain) et les infos météo sur 100 caractères
typedef struct{

    int pid;
    char reponse[100];

} Treponse;
