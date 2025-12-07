GMHS_2526_PlantBox.ino
Arduino controller for plant box sensors and motors

Functionality:
1) Use 1 motor and 1 moisture sensor to add moisture to a plant grow-bed.
Activate the motor for a finite time when the moisture drops below a 
minimum threshold to extend lead screw. Retract the motor lead screw 
when fully extended to allow for removal/replacement of water bag.

2) Use I2C accelerometer to detect changes in gravity and when plant box 
is in null-gravity environment.  

Resources:
TB6612 SparkFun Library: https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library
BMA400 SparkFun Library: https://github.com/sparkfun/SparkFun_BMA400_Arduino_Library
