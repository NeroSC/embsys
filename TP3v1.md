Corentin Néron
Thomas Le Masson
TP: Part 3

# Partie 3: Multiplexage, threads, mutex et IPC

## Exercice 1 : Multiplexage

**Question 1** : Selon vous, à quoi correspond le champs indiqué par
                *PTTY*?

PTTY est un terminal emulator type SSH qui permet l'accès GPS. 

**Question 2** : En regardant le code de *reader.c*, y a-t-il quelque chose qui vous chagrine?

Le code n'est pas documenté. Pas de gestion de SIGINT.


**Question 3** : Grâce à des recherches Internet (ou en fouinant dans le code du simulateur), déterminez dans quelle trame et dans quel champs l'heure est définie.

$GPVTG,055.4,T,035.1,M,006.3,011.6,K
$GPGLL,4841.10,N,00745.50,E,104113,A  -> 10:41:13


**Question 4** : Quelles fonctions sont utilisées dans *reader.c* pour
                 ouvrir/écouter/lire/fermer le port virtuel du simulateur?
                 Comment s'appelle ce type de programmation?

open(), select(), read(), close() il s'agit du multiplexage.


**Question 5** : Modifiez le code de *reader.c* afin qu'il puisse écouter les trames provenant de deux simulateurs GPS différents (ports paramétrables au lancement). Vérifiez le bon fonctionnement enlançant deux instances du simulateur GPS.
        
Ca marche bien ! cf code https://github.com/NeroSC/embsys


**Question 6** : Utilisez *syslog* pour afficher l'heure dans la console ainsi que le PID du père.

Pour accéder au fichier syslog, il faut se placer dans le répertoire var/log/.


**Question 7** : TODO!!!! Modifier la conf du démon syslog pour logger dans un fichier spécifique!


### À retenir

  * comment utiliser *getopt* pour passer des paramètres en ligne de commande
    à votre application
  * comment utiliser *select* pour monitorer plusieurs file descriptors
  * l'utilisation globale de *syslog*


## Exercice 2 : Mémoire partagée et sémaphore

Comme vu précédement, le simulateur GPS envoie les données sur un port virtuel
à travers /dev/pts/X.

Le binaire *shm_writer* présent dans le répertoire *shm_writer* lit les données
envoyées par le simulateur GPS sur le port virtuel et écrit en mémoire partagée
les informations *latitude*, *longitude* et *time*.

Pour compiler le binaire *shm_writer* :

````
$ cd labs/2_sysprog_part2/src/shm_writer
$ make
````

Les données en mémoire partagée sont représentées via la structure SHDATA
définie dans le header *shm_writer/shdata.h* :

````
struct SHDATA
{
    float latitude;
    float longitude;
    int time;
};
````

Le but de cet exercice est de lire la mémoire partagée remplie par le binaire
*shm_writer* et d'afficher ces informations à l'écran toutes les secondes en
modifiant le code de *shm_reader*.

Tout d'abord, ouvrez un terminal et lancez le simulateur GPS :

````
$ cd gps
$ sh run.sh
PTTY: /dev/pts/X

````

Ouvrez un second terminal et lancez le binaire *shm_writer* :

````
$ cd shm_writer
$ ./shm_writer -p /dev/pts/X -s myshm -l lock

````

**Question 1** : Selon vous, à quoi correspond le paramètre *myshm* indiquée via
                 l'option *-s* de *shm_writer*? Et *lock*?

**Question 2** : Où peut-on trouver la représentation du segment de mémoire
                 partagée sur le système de fichiers?

**Question 3** : Faites un schéma bloc des différents éléments mis en jeu.

Placez vous dans le répertoire *shm_writer*.

**Question 4** : En étudiant la fonction *hndopen* implémentée dans le fichier
                 *handler.c*, décrivez les fonctions utilisées pour gérer le
                 segment de mémoire partagée.

**Question 5** : Quelle fonction utilise le paramètre *myshm* passé en ligne de
                 commande?

**Question 6** : Quel flag en particulier indique une *création* de segment
                 et pas seulement une ouveture en lecture/écriture?

Placez vous maintenant dans le répertoire 2_sysprog_part2/src/shm_reader.

**Question 7** : Modifiez la fonction *hndopen* implémentée dans *handler.c*
                 pour ouvrir le segment de mémoire partagée en lecture/écriture.
                 Les champs *shm*, *shmfd* et *shdata* de la structure
                 *handlers* passée en paramètre doivent être mis à jour.

En voulant compiler le binaire *shm_reader*, vous devez obtenir ceci :

````
$ make
/tmp/ccawsZJY.o: In function `hndopen':
handler.c:(.text+0x66): undefined reference to `shm_open'
collect2: error: ld returned 1 exit status
````

Pour utiliser les fonctions liées à la mémoire partagée, la librairie *realtime*
est nécessaire.

**Question 8** : En s'inspirant de *shm_writer/Makefile*, modifiez le fichier
                 *shm_reader/Makefile* pour que la compilation passe.

Une fois la compilation réalisée avec succès, exécutez *shm_reader*. Vous devez
obtenir :

````
$ make
$ ./shm_reader -s myshm -l lock
time : XXXXXX

time : XXXXXX

...
````

**Question 9** : Expliquez l'évolution de la valeur *time* affichée à l'écran.

Dans le main de *shm_reader*, le paramètre *handlers* est défini en tant que
variable globale.

**Question 10** : Quelle est la particularité d'une variable globale? Comment
                  fait-on pour définir une telle variable?

**Question 11** : Dans le *main* de shm_reader.c, complétez la boucle *while* de
                  la fonction shmreader afin que les champs *latitude* et
                  *longitude* du segment de mémoire partagée *handlers.shdata*
                  soient affichés en même temps que le champ *time*.

**Question 12** : Inspirez vous de la fonction *decode_frame* de
                  shm_writer/shm_writer.c pour lever/baisser le sémaphore lors
                  de la lecture du segment de mémoire partagée dans la fonction
                  *shmreader* de *shm_reader.c*.

Recompilez et exécutez *shm_reader*. Vous devez obtenir :

````
$ make
$ ./shm_reader -s myshm -l sem
time : XXXX
latitude : XXXX
longitude : XXXX

time : XXXX
latitude : XXXX
longitude : XXXX

...
````

Modifiez la fonction *sem_open* utilisée dans la fonction *hndopen* et définie
dans *shm_writer/handler.c* de cette manière :

````
// handlers->sem = sem_open(opts.sem, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR, 1);
handlers->sem = sem_open(opts.sem, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR, 0);
````

Recompilez *shm_writer*. Relancez *shm_writer* puis *shm_reader*.

**Question 13** : Que se passe t-il côté *shm_reader*? Pourquoi? Quel effet a eu
                  la modification précédente?

Rétablissez l'appel à *sem_open* du fichier *shm_writer/handler.c* ainsi :

````
handlers->sem = sem_open(opts.sem, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR, 1);
````

Lorsque l'utilisateur interrompt le processus via Ctrl-C, la fonction *hndclose*
n'est jamais appellée et les handlers d'entrées/sorties ne sont pas fermés
correctement.

**Question 14** : Mettez en place un gestionnaire de signaux qui appelle la
                  fonction *hndclose* lors d'une interruption. Inspirez vous de
                  *shm_writer/shm_writer.c*.

**Question 15** : Comparez la fonction *hndclose* définie dans
                  *shm_writer/handler.c* avec celle définie dans
                  *shm_reader/handler.c*. Quelle différence voyez vous?
                  Expliquez.

### À retenir

  * la notion de variable globale
  * les fonctions permettant de gérer les segments de mémoire partagée :
    *shm_open*, *ftruncate*, *mmap* et *shm_unlink*.
  * l'utilisation de *sem_open*, *sem_wait* et *sem_post*.
