#include <Servo.h>
#include <CapacitiveSensor.h>


Servo myservo;  // create servo object to control a servo
CapacitiveSensor cs_7_8 = CapacitiveSensor(7,8); //10M Resistor between pins 7 and 8, you may also connect an antenna on pin 8. If the antenna is connected to pin 7 it will sense touch-release...
unsigned long csSum; // This variable stores accumulates capacitive values till reaching a threshold

//Variables for encoding servo positions
int ServoMotorOutPosition = 0; //Variable to store a value for the servo motor position where it is out of reach
int ServoMotorInPosition = 120; //Variable to store a value for the servo motor position where it is in reach
int CurrentServoMotorPosition = 0; //Variable to store the current position of the servo motor
int i = 0;

//Variables to for storing input value changes and input states of the input pin to control servo motor
int InputState = 0;
volatile bool InputChange = false; //Volatile bool for variables in attached interrupt


void setup() {
    Serial.begin(9600); // Begin serial communication
    pinMode(12, OUTPUT); //LED (to signal touches) is on pin 12 
    myservo.attach(9);
    pinMode(3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(3), DetectInputChange, CHANGE);
    delay(50);
    myservo.write(ServoMotorOutPosition);
    CurrentServoMotorPosition = myservo.read();
    Serial.println(CurrentServoMotorPosition);
}

void loop() {
  noInterrupts();
  CapacitiveSensorRead(); // This time we put everything in a function
  ServoMotorInOut();
  interrupts();
}

void CapacitiveSensorRead() {
    long cs = cs_7_8.capacitiveSensor(80); // Sensor resolution is set to 80; will store the capacitance as an arbitrary value
	if (cs > 100) { //Arbitrary number; lower threshold
		csSum += cs; // Same as csSum = csSum + cs ; cumulative value for reachiung threshold
		Serial.println(cs); 
		if (csSum >= 3800) //Testing if csSum reached threshold, a High value means it takes longer to trigger
		{
			Serial.print("Trigger: ");
			Serial.println(csSum);
      BlinkLEDandTTLout();
			if (csSum > 0) { csSum = 0; } //Reset of csSum
			cs_7_8.reset_CS_AutoCal(); //Stops readings and recalibration of capacitive sensor
		}
	} else {
		csSum = 0; //Timeout caused by bad readings
	}
}

void BlinkLEDandTTLout() {
      digitalWrite(12, HIGH);  //  if a lick is detected, turn LED ON.
      delay(1);
      digitalWrite(12, LOW);  //  turn the LED OFF.
  }

void DetectInputChange() {
    InputChange = true;
    Serial.println("Change Detected");
}

void ServoMotorInOut() {
  if (InputChange==true) { // If there was a change of state on the input pin
    InputState = digitalRead(3); // Detect to which state it hast changed...high or low...high means in low means out
    if (InputState == HIGH) { // If the state is high rotate the servo to the in position
      for (i = CurrentServoMotorPosition; i <= ServoMotorInPosition; i += 1) {
        myservo.write(i); delay(15);
        }
        CurrentServoMotorPosition = myservo.read(); //save the current position of the servo
    } else { // otherwise rotate it to the out position
      for (i = CurrentServoMotorPosition; i >= ServoMotorOutPosition; i -= 1) {
        myservo.write(i); delay(15);
        }
        CurrentServoMotorPosition = myservo.read(); //save the current position of the servo
    }
    InputChange == false; //Reset Change Detection to no change detected
  }
}


