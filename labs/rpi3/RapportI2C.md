# BME280

## Activation du support de l'I2C



**Question 1**: Réalisez un schéma de brochage simple de la connection entre la     
                RPI3 et le BME280.
                
Done.

**Question 2**: Décrivez rapidement l'utilité de chaque broche.

VIN : alimentation 3V
GND : masse
SCK : serial clock
SD1 : channel 

**Question 3**: Une fois le BME280 connecté, relancez la commande
                *i2cdetect -y 1*. Quelle différence observez-vous par
                rapport à tout à l'heure.

On observe un 77 en dernière position du bus. 

**Qestion 4**: En lisant la page 32 de la
[datasheet](https://www.embeddedadventures.com/datasheets/BME280.pdf), cette
               différence vous parait-elle normale? 
               
Cela correspond à une slave adresse qui permet l'accès en écriture et donc la communication avec le BME280.

## Driver du BME280

Le driver officiel fournis par le constructeur est ici: https://github.com/BoschSensortec/BME280_driver

**Question 5**: Utilisez l'API C du driver pour récupérer les données de
                température, de pression et d'humidité fournies par le capteur.


