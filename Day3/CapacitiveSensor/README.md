

Today we will build a capacitive touch sensor. The sensor will be combined with a servo motor to control the positioning in perspective of an imaginary animal. When the antenna of the sensor is soldered to a cannula, it can be perfectly used for touch/lick detection and direct reward delivery via the extended sensor (would require loop triggering of a solenoid valve or syringe pump via a DAQ or similar).

In this part of the course, the aim is also to build the device as an independent unit (without connection to a PC!). We will therefore use serial communication for proof of principle and debugging only. The device will be able to communicate via TTL (transistor-transistor logic) signals from BNC ports. This allows for communication with a vast number of other devices and DAQs while avoiding integration hell.

Combining a capacitive sensor and the control of a servo motor can be a difficult task, due to running computational tasks in parallel. Luckily, Arduino provides a hardware interrupt to facilitate parallel computing. We will learn to implement this function for creating a reliable machine.

Together, we will go through 5 increasingly complex coding blocks and circuit diagrams:

- 01_CapacitiveSensor_SerialCom (Printing raw capacitance via serial communication)
- 02_CapacitiveSensor_Thresh (Adding a threshold for touch induced triggering)
- 03_CapacitiveSensor_ThreshTTL (touch will blink an LED or send a TTL signal to a DAQ)
- 04_CapacitiveSensor_ThreshTTL_attachInterrupt (Attaching an interrupt to a pin to control servo motor motion via BNC)
- 05_CapacitiveSensor_ThreshTTL_attachInterrupt_ServoControl (Turing the servo and sensor into position for an animal)

You are free to try your own version of code first. But be reassured that there is a working version of code ready if you get stuck somewhere.

We provide all necessary devices (oscilloscope and triggering device) for you to test your device/code.





Links to necessary resources and libraries:

The current design was modified from the following source:

- https://scanbox.org/2016/04/14/a-simple-lick-o-meter-and-liquid-reward-delivery-system/


Capacitive sensor library main source (GitHub):

- https://github.com/PaulStoffregen/CapacitiveSensor

Capacitive sensor library examples:

- https://playground.arduino.cc/Main/CapacitiveSensor/


Servo library:

- https://www.arduino.cc/reference/en/libraries/servo/

Servo Library original source (GitHub):

- https://github.com/arduino-libraries/Servo

Documentation of attached interrupt:

- https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/