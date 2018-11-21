Corentin Néron
Thomas Le Masson
TP: Part 1

# Partie 1: Utilisation d'un simulateur GPS


**Question 1**: Qu'est ce qu'un Makefile? À quoi sert make?

Un Makefile est un fichier comportant un certains nombre de règles de construction de fichiers exécutables. make est un logiciel appelé via une commande du même nom qui permet de lire un fichier Makefile et de construire les fichiers nécessaires indiqués par le Makefile selon les règles indiquées par ce dernier.

**Question 2**: Quel compilateur est utilisé ici?

Le compilateur utilisé est gcc. 

**Question 3**: Qu'est ce qu'une librairie partagée?

Une librairie partagée est utilisé par un programme au moment où il est exécuté, ce qui permet à plusieurs programme d’utiliser cette même librairie. 

**Question 4**: Donnez un exemple de fichier C et la ligne de commande
correspondante pour obtenir un binaire exécutable (un hello    world par exemple).
Avec un fichier  hello_word.c de type 

#include<stdio.h>








int main()


{


    printf("Hello, world!");


    return 0;


}
Ligne de commande :  gcc -Wall -o hello_world hello_world.c

**Question 5**: Donnez un exemple de fichier C et les lignes de commandes correspondantes pour obtenir une librairie partagée.

Pour compiler un objet partagé, il faut utiliser la commande : gcc -Wall -o hello_world.so -shared hello_world.o

