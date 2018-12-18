Thomas le Masson
Corentin Néron

# Partie 3: Flashage de la carte et Bootloader


**Question 1**: Une fois le flashage terminé, combien y-a t-il de partition
                sur la carte SD? Que contiennent-elles?

La carte SD contient 2 partitions. /dev/sdb1    /dev/sdb2
Une avec 32MB W95 FAT32 bootable, l'autre 200M Linux.

**Question 2**:  Quels sont les ports TX/RX?

Les ports TX/RX sont sur les fiches GPIO14/15. Ils permettent d'interfacer les capteurs et autres devices.

**Quesion 3**: Quelle est la configuration du port série permettant une
               communication avec la RPI3 (baud, etc)?

D'après le fichier cmdline.txt sur la premiere partition de l'image montée: 
baud = 115200

user, pw: user1*

**Question 4**: Déterminez l'adresse IP de votre RPI3. Quelle commande
                avez-vous utilisé?

ifconfig : 170.20.10.201


**Question 5**: Testez la connection ssh en tant que *user* et *root*. Quelle
                différence observez-vous? Pourquoi? Où est-ce configuré?

ssh user@170.20.10.201 il est possible de se connecter, tandis qu'avec le root cela ne fonctionne pas.
Cela permet d'empêcher l'accès au root et de modifier les paramètres, c'est une protection.
Cette option est configurée dans le fichier sshd.config *PermitRootLogin*


### U-Boot



**Question 6**: En cherchant sur le net, trouvez l'utilité des commandes U-Boot
                *fatload*, *setenv* et *bootz*.

*fatload* Commande qui permet de charger un fichier à partir d'un volume de stockage.
*setenv* Change ou ajoute une variable d'environnement.
*bootz* boot Linux l'image de zImage à partir de la mémoire.

Puis compiler ce fichier avec *mkimage*:

````
# ./output/host/bin/mkimage -A arm -O linux -T script -C none -a 0x00000000 \
    -e 0x00000000 -n boot.scr -d boot.source boot.scr
````

Ensuite copiez le fichier *boot.scr* sur la 1ère partition de la carte SD aux
côtés du binaire de U-Boot.

La dernière étape consiste à modifier le fichier
[config.txt](https://www.raspberrypi.org/documentation/configuration/config-txt/)
pour indiquer au firmware de la RPI3 de charger U-Boot au lieu du kernel:

````
kernel=u-boot.bin
enable_uart=1
dtoverlay=pi3-disable-bt
````

C'est ensuite U-Boot qui se chargera de charger le kernel comme indiqué dans
le fichier *boot.source* (cf étape précédente).

Désormais, connectez vous avec un terminal série et démarrez la RPI3. Appuyez
sur n'importe quelle touche de votre clavier dans le terminal série pour
interrompre la phase de boot et ainsi ouvrir le prompt U-Boot:

<p align="center">
  <img src="https://github.com/pblottiere/embsys/blob/master/labs/rpi3/imgs/uboot_prompt.png" width="550" title="Github Logo">
</p>

Dans ce prompt, la commande *help* permet de lister les commandes disponibles.

**Question 7**: À quoi sert la commande *version*? Que retourne t-elle comme
                informations?

Pour reprendre la phase normale de boot et démarrez le kernel, lancez la
commande *boot*.

### U-Boot et server TFTP

L'objectif de cette partie est de charger l'image du kernel *zImage* non pas à
partir de la carte SD comme dans la partie précédente, mais grâce à un serveur
TFTP.

**Question 8**: Trouvez une documentation en ligne afin de configurer un serveur
                TFTP sur votre machine hôte. Note: il faut que la machine hôte
                et la RPI3 soit dans le même sous-réseau (autrement dit, il faut
                qu'elles puissent se pinger).

Pour tester le bon fonctionnement du serveur, lancez la commande suivante à
partir de la RPI3 pour récupérer le fichier *zImage*:

```
# tftp <tftp_server_ip> -r zImage -g
```

Si le fichier *zImage* est bien récupéré, cela signifie que le serveur TFTP est
correctement configuré.

Ensuite, modifiez le fichier *boot.source* pour obtenir:

```
mmc dev 0
fatload mmc 0:1 0x2000000 bcm2710-rpi-3-b.dtb
setenv autoload no
dhcp
tftp ${kernel_addr_r} ${serverip_tftp}:zImage
setenv bootargs 8250.nr_uarts=1 root=/dev/mmcblk0p2 rootwait console=ttyS0,115200
bootz ${kernel_addr_r} - 0x2000000
```

**Question 8**: À quoi servent les comandes *dhcp* et *tftp*?

Puis recompilez ce fichier avec *mkimage* comme précédemment. Pensez ensuite à
copier le fichier *boot.scr* résulant sur la 1ère partition de la RPI3.

Finalement, redémarrez la RPI3 et intérrompez la phase de boot pour arriver
dans le prompt de U-Boot. Sauvegardez l'addresse IP de votre serveur TFTP:

```
U-Boot> setenv serverip_tftp <tftp_server_ip>
U-Boot> saveenv
```

**Question 9**: Décrivez les commandes précédente.

Finalement, redémarrez une dernière fois la RPI3 et observez le chargement du
kernel:

<p align="center">
  <img src="https://github.com/pblottiere/embsys/blob/master/labs/rpi3/imgs/uboot_tftp_kernel.png" width="550" title="Github Logo">
</p>
