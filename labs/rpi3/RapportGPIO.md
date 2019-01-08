Thomas le Masson et Corentin Néron

# Partie 5 : GPIO et relais

Numérotation des pins pour la RPi3 Model B v1.2:

## GPIO et LED

### Sysfs

**Question 1**: Grâce à la documentation du kernel sur
                [sysfs](https://www.kernel.org/doc/Documentation/gpio/sysfs.txt),
                allumez et éteignez la LED connectée à la GPIO 17.
                
echo 17 > export 
cd sys/class/gpio/gpio17
echo out > direction
echo 1 > value

### Python


**Question 2**: Utilisez cette API Python pour allumer/éteindre la LED
                connectée à la GPIO 17 (faire attention au mode BCM ou BOARD).

>>> import RPi.GPIO as GPIO
>>> GPIO.setmode(GPIO.BOARD)
>>> GPIO.setup(11, GPIO.OUT)
>>> GPIO.output(11,GPIO.HIGH)

### PWM

**Question 3**: Modifiez la fréquence et le duty_cycle pour faire varier la
                luminosité de votre LED.
>>> import RPi.GPIO as GPIO
>>> GPIO.setmode(GPIO.BOARD)
>>> GPIO.setup(12, GPIO.OUT)
>>> p = GPIO.PWM(12, 0.5)
>>> p.start(1)
>>> p.stop()

## Relais

**Question 4**: Testez l'allumage de la LED via le contrôle de la GPIO par Sysfs
                et Python.

sysfs:

echo 4 > export 
cd sys/class/gpio/gpio4
echo out > direction
echo 1 > value  

Python: 
>>> import RPi.GPIO as GPIO
>>> GPIO.setmode(GPIO.BOARD)
>>> GPIO.setup(7, GPIO.OUT)
>>> GPIO.output(7,GPIO.HIGH)
                
