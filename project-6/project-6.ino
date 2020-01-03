//Light-based Theremin

int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  while (millis() < 5000) {

    sensorValue = analogRead(A0);
    //calibrate a range of sensor values for baseline room light conditions
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow) {
      sensorHigh = sensorValue;
    }

  }
  //indicates end of calibration by turning LED off
  digitalWrite(ledPin, LOW);
}

void loop() {
  sensorValue = analogRead(A0);
  //B0 to B6
  int pitch = map(sensorValue, sensorLow, sensorHigh, 31, 1976);
  //tone function parameters (pin, Hz, ms)
  tone(8, pitch, 20);

  delay(10);

}
