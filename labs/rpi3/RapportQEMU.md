Thomas le Masson
Corentin Néron

# Partie 2: QEMU

Dans cette partie, nous allons voir comment se servir de chroot et QEMU pour
naviguer dans le RFS compilé par Buildroot pour la RPI3.

### Préliminaires

Ce TP est à réaliser à partir de la même image Docker que la
[Partie 1](buildroot.md):

````
$ docker run -it --privileged pblottiere/embsys-rpi3-buildroot /bin/bash
# cd /root/
# tar zxvf buildroot-precompiled-2017.08.tar.gz
# cd buildroot-precompiled-2017.08
````

**Question 1**: À quoi sert l'option *--cap-add* lors du lancement d'un
                nouveau coneneur Docker?

*--cap-add* sert à ajouter une capacité Linux non autorisée par défaut telles que : 
	SYS_MODULE Load and unload kernel modules.
	SYS_RESOURCE 	Override resource Limits.


**Question 2**: À quoi sert la commande *chroot*?

*chroot* Change Root, permet de changer de répertoire racine vers un nouvel emplacement. 

Ensuite, exécutez le binaire cross-compilé *hw* dans l'environnement *chroot*.

**Question 3**: Que se passe-t-il? Pourquoi?

Le fichier s'exécute et affiche Hello Worlds dans la console puisqu'on a compilé le fichier à l'aide de arm-linux-gcc.


