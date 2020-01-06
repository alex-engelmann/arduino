// Project 8 - Digital Hourglass
//adjusted to measure 30s instead of 1 hour, easier to test

const int switchPin = 8;
unsigned long previousTime = 0;
int switchState = 0; 
int prevSwitchState = 0; 
int led = 2;

// 5000ms = 5s
long interval = 5000; 

void setup() {
  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
  pinMode(switchPin, INPUT);
}

void loop() {
  // store the time since the Arduino started running in a variable
  unsigned long currentTime = millis();

  if (currentTime - previousTime > interval) {
    previousTime = currentTime;

    digitalWrite(led, HIGH);
    // increment the led variable
    // in 10 minutes the next LED will light up
    led++;

    if (led == 7) {
      // the hour is up
    }
  }

  // read the switch value
  switchState = digitalRead(switchPin);

  // if the switch has changed
  if (switchState != prevSwitchState) {
    // turn all the LEDs low
    for (int x = 2; x < 8; x++) {
      digitalWrite(x, LOW);
    }

    // reset the LED variable to the first one
    led = 2;

    //reset the timer
    previousTime = currentTime;
  }
  // set the previous switch state to the current state
  prevSwitchState = switchState;
}
