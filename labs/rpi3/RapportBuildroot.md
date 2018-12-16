Thomas Le Masson
Corentin Néron

# Partie 1: Construction d'OS avec Buildroot et chaine de cross-compilation




**Question 1**: 
==============


'configs/embsys_defconfig':

'busybox.config':

'users.table': contient l'utilisateur, le groupe auquel il appartient, ainsi que le repo dans lequel il évolue.

**Question 2**: 
==============

Le fichier de configuration Buildroot à utiliser : *configs/raspberrypi3_defconfig/*


**Question 3**: 
===============

Le répertoire package contient différentes informations pour chaque application/process installés, fichier config, .hash et .mk

**Question 4**: 
==============

*package/openssh*

.hash verifier l'intégrité, .mk makefile, fichiers ssh pour accès à distance sécurisé, fichier config pourles autotools. 

**Question 5**:
==============

*board/raspberrypi3/*
contient les fichiers de config pour raspberrypi et les fichiers de lancement du build.

**Question 6**
==============

La commande #make embsys_defconfig permet de définir les options de compilation et de lancement à appliquer. 


**Question 7**: En naviguant dans le menu, repérez:
- l'architecture matérielle cible : ARM arch/Config.in:261 
- le CPU ciblé : cortex A63 arch/Config.in:273
- l'ABI (en rappellant la signification de celle choisie) : EABIhf Embedded ABI Hard Float
- la librairie C utilisée: uClibc-ng
- la version du cross-compilateur: gcc 6.x
- la version du kernel : custom kernel de https://github.com/rapsberrypi/linux.git




**Question 8**: 
Fichier configuration embsys_defconfig :BR2_PACKAGE_OPENSSH=y
           

**Question 9**: Qu'est ce que busybox? À quoi sert la commande
                *make busybox-menuconfig*? Qu'obtiens t'on et que pouvons
                nous faire?

Busybox est un logiciel qui implémente des commandes standard sous linux.
*make busybox-menuconfig* permet de lancer le terminal de configuration busybox 




**Question 10**: Que contient le répertoire *output/host*? À quoi correspond
                 le binaire *output/host/usr/bin/arm-linux-gcc*?

*output/host* contient une image du système de fichier linux de l'OS cible précompilé
*output/host/usr/bin/arm-linux-gcc* est le binaire du compilateur

**Question 11**: Décrire le résultat de la commande *file*. Que se passe t-il
                 si vous exécutez la commande *./hw*?

*file* est une commande qui permet d'obtenir le type d'un fichier. on voit que le fichier a été compilé pour être exécuté sur cet ordinateur
*./hw* permet l'exécution du fichier dans la console. 

**Question 12**: Utilisez la commande *file* sur le binaire résultant.
                 Quelle différences constatez vous par rapport au cas précédent
                 (binaire généré avec gcc)? Que se passe t-il si vous essayez
                 d'exécuter la commande *./hw*? Expliquez pourquoi.
*file*Ici on voit que le binaire est compilé pour être utilisé sur l'architecture cible : ARM 32bits
*./hw* Une erreur se produit puisque le fichier n'a pas été compilé pour être utilisé sur l'architecture de l'ordinateur que nous utilisons.

**Question 13**: Que contient le répertoire *output/images*? Décrivez notamment
                 l'utilité des fichiers *rootfs.tar*, *zImage* et *sdcard.img*.
                 
output/images contient les images compilées de l'OS
rootfs.tar doit être le Root File System, compressé au format tar
zImage est l'image du noyau Linux
sdcard.img 

**Question 14**: Que vous dis les résultats de la commande *file* lorsque vous
                 l'utilisez sur les fichiers *zImage* et *sdcard.img*?

*file zImage* : zImage: Linux kernel ARM boot executable zImage (little-endian)
*file sdcard.img*: sdcard.img: DOS/MBR boot sector; partition 1 : ID=0xc, active, start-CHS (0x0,0,2), end-CHS (0x4,20,17), startsector 1, 65536 sectors; partition 2 : ID=0x83, start-CHS (0x4,20,18), end-CHS (0x1d,146,54), startsector 65537, 409600 sectors

**Question 15**: Que contient le répertoire */tmp/rootfs*?

*/tmp/rootfs* contient le système de fichier qui sera présent sur la machine cible
