#Projet de C - 1er Quadrimèstre 2012-2013
-----

Projet réalisé dans le cadre du cours de Système d'Exploitation Travaux Pratiques par **Antoine BETAS** et **Cédric BREMER**, 2TL1, Ephec Louvain-La-Neuve

##Consignes et échéances

* Travail à défendre lors de l'examen oral le 16/1 à 9h40
* Remettre en même temps le rapport écrit, voir projet C de l'an passé

##Contenu du répertoire

* Dossier [code](https://github.com/Ephec/C-Projet/tree/master/code) reprenant l'ensemble du code source et des éventuelles bibliothèques
* Dossier [documents](https://github.com/Ephec/C-Projet/tree/master/documents) contenant le rapport ainsi que les autres documents utiles

* Pour cloner le repertoire `git clone git://github.com/Ephec/C-Projet.git`
* Pour télécharger le zip de répertoire `https://github.com/Ephec/C-Projet/archive/master.zip`

##But du projet

Réaliser un système de communication entre différents programmes (avec plusieurs processus) via un fichier de type FIFO. Un serveur ATIS fournit les informations à des pilotes (clients) via un FIFO individuel par client. Les demandes des pilotes sont envoyées sur un seul et même FIFO pour tous. Les piloes s'identifient via leurs PID (getpid()). Enfin le serveur répond au client en fonction des informations météo se trouvant dans un fichier texte. Ces informations sont générées par un programme météo qui change la météo à interval régulier.

##Licence

Ce code est sur Github donc il est libre à vous de l'utiliser comme bon vous semble. Dans le cadre de cours, sachez que ne pas citer ses sources ou alors recopier intégralement le code d'un autre ne vous avancera à rien (voir pire). Si ce travail peut vous aider, n'hésitez pas à vous en INSPIRER !
