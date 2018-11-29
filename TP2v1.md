Corentin Néron
Thomas Le Masson
TP: Part 2

# Partie 2: Compilation, debug et gestionnaire de signaux


## Exercice 1 : GDB et fichier core

**Question 1** : Que se passe-t-il au bout de quelques secondes? Qu'en
                 déduisez vous?

Une segmentation fault apparaît, il y’a donc un problème d’accès mémoire.

**Question 2** : Quel signal a reçu le processus pour se terminer ainsi? Comment
                vérifiez vous le numéro du signal reçu?

echo $? -> 139 - 128 = 11 -> SIGSEGV

**Question 3** : Grâce à GDB et au fichier *core* généré, analysez la source du problème du binaire *gps*. Quelle partie du code est fausse? Pourquoi?

En  utilisant gsb,  l’erreur de segmentation se trouve dans la fonction knot_to_kmh_str() de la librairie libnmea.so. La ligne puts(NULL) renvoie une erreur puisque la fonction puts attend un char.

**Question 4** : Que se passe-t-il quand vous lancez GDB en mode interactif sur  le binaire *gps*?
gdb n'exécute pas le simulateur car il manque la librairie partagée libptmx.so.

**Question 5** : À quoi sert la commande *ldd*? Quelle information
                supplémentaire cela vous apporte-t-il?

ldd permet de voir quelles sont les librairies partagées. On se rend compte qu’il manque aussi la librairie libnmea.so en plus de lbptmx.so.

**Question 6** : Comment résoudre ce problème en tant qu'utilisateur? N'hésitez pas à regarder le fichier *gps/run.sh*.

En utilisant ./run.sh au lieu de sh run.sh, on peut charger les librairies partagées dans le même terminal dans lequel gdb est ensuite lancé et donc résoudre le problème.

**Question 7** : Quelle est la différence entre les commandes *s* et *n* dans le prompt gdb suite à un breakpoint?

n -> next permet d’avancer de fonction à fonction
s -> step permet d’avancer ligne par ligne


**Question 8** : Dans quel contexte ce type d'outils peut être intéressant?

Dans le cadre de débug de programmes d’équipements distants.

## Exercice 2 : LD_PRELOAD et sigaction


**Question 1** : Implémentez dans le fichier hook.c la fonction à l'origine du problème repéré au sein du simulateur GPS mais cette fois-çi sans erreur.

cf code https://github.com/NeroSC/embsys


**Question 2** : Éditez le Makefile pour compiler *hook.c* sous la forme d'une librairie partagée nommée *libhook.so* (s'inspirer de *gps/src/lib/ptmx/Makefile*). Testez la compilation.

Ca marche bien.


**Question 3** : Éditez le fichier *run.sh* pour utiliser LD_PRELOAD au moment de lancer le simulateur et ainsi hooker le binaire avec la librairie libhook.so. Exécutez run.sh : le simulateur ne doit plus partir en segfault.

cf code https://github.com/NeroSC/embsys


**Question 4** : Utilisez le *man* pour déterminer le prototype de la fonction *printf* (expliquez comment vous utilisez *man* dans ce cas et pourquoi). Comment est appelé ce type de fonction?

int printf(const char* format, ...);
les “...” signifient que printf est une fonction variadique. On peut faire afficher autant de variables que l’on veut.

**Question 5** : Analysez *gps/src/bin/gps/gps.c* er repérez où se trouve le gestionnaires de signaux. Décrivez les fonctions utilisez ainsi que les signaux gérés.




**Question 6** : Hookez le simulateur pour que ce dernier ne puisse plus
                 être interrompu par le signal SIGINT (Ctrl-C) en
                 réimplémentant la fonction *printf* dans libhook.so. Pour
                 cela, utilisez la fonction *sigaction* pour mettre en place
                 un gestionnaire de signaux au sein même de la fonction
                 *printf*  réimplémentée.

**Question 7** : Comment faire pour interrompre le processus étant donné que ce dernier ne répond plus au Ctrl-C? Citez deux méthodes.

**Question 8** : En regardant le fichier *gps/Makefile*, que pouvez-vous dire de la règle *ok*? À quoi sert-elle et comment fonctionne-t-elle?
