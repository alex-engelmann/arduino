//4-note keyboard

//C, D, E, F

int notes[] = {262, 294, 330 , 349 };

void setup() {
  Serial.begin(9600);
}

void loop() {
  int keyVal = analogRead(A0);
  Serial.println(keyVal);

  switch (keyVal) {
    case 1023:
      tone(8, notes[0]);
      break;
    case 990 ... 1010:
      tone(8, notes[1]);
      break;
    case 505 ... 515:
      tone(8, notes[2]);
      break;
    case 5 ... 10:
      tone(8, notes[3]);
      break;
    default:
      noTone(8);
      break;
  }
}
