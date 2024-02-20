#include <CapacitiveSensor.h>
CapacitiveSensor cs_7_8 = CapacitiveSensor(7,8); //10M Resistor between pins 7 and 8, you may also connect an antenna on pin 8. If the antenna is connected to pin 7 it will sense touch-release...

void setup() {
    Serial.begin(9600); // Begin serial communication
}

void loop() {
    long cs = cs_7_8.capacitiveSensor(80); // Sensor resolution is set to 80; will store the capacitance as an arbitrary value
    delay(10); //delay to reduce serial prints
    if (cs > 10) { //sets a threshold for serial printing in order to reduce serial communication and not print too much...
      Serial.println(cs);
    }   
}