/*
 Controlling a servo position using a potentiometer (variable resistor)
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int const potpin = A0;  // analog pin used to connect the potentiometer
int potVal;    // variable to read the value from the analog pin
int angle;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  // reads the value of the potentiometer (value between 0 and 1023)
  potVal = analogRead(potpin);
  Serial.print("potVal: ");
  Serial.print(potVal);
  // scale it to use it with the servo (value between 0 and 180 - my servo is about 170)
  angle = map(potVal, 0, 1023, 0, 170);
  Serial.print(" , angle: ");
  Serial.println(angle);
  
  myservo.write(angle);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
