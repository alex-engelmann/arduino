const int switchPin = 2;
const int motorPin = 9;
int switchState = 0;


void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(switchPin, INPUT);
}

void loop() {
  switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    //this is for regular on/off
    //digitalWrite(motorPin, HIGH);
    //this allows PWM (range from 0 to 255)
    analogWrite(motorPin, 80);
  }
  else {
    digitalWrite(motorPin, LOW);
  }

}
