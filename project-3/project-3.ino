#include <math.h>

#define ThermistorPIN 0
// Analog Pin 0

// room temperature in Celsius
const float baselineTemp = 20.0;

float vcc = 5.00;
// only used for display purposes, if used
// set to the measured Vcc.
float pad = 9970;
// balance/pad resistor value, set this to
// the measured resistance of your pad resistor
float thermr = 10000;
// thermistor nominal resistance

float Thermistor(int RawADC) {
  long Resistance;
  float Temp;  // Dual-Purpose variable to save space.

  Resistance = pad / ((1024.0 / RawADC) - 1);
  Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius

  //BEGIN- Remove these lines for the function not to display anything

  Serial.print("ADC: ");
  Serial.print(RawADC);
  Serial.print("/1024");                           // Print out RAW ADC Number
  Serial.print(", vcc: ");
  Serial.print(vcc, 1);
  Serial.print(", pad: ");
  Serial.print(pad / 1000, 2);
  Serial.print(" kOhms, Volts: ");
  Serial.print(((RawADC * vcc) / 1024.0), 3);
  Serial.print(", Thermistor resistance: ");
  Serial.print(Resistance);
  Serial.print(" Ohms, ");

  // END- Remove these lines for the function not to display anything
  return Temp;
}

float sample(byte z)
// This function will read the Pin 'z' 5 times and take an average.
{
  byte i;
  float sval = 0;
  for (i = 0; i < 5; i++)
  {
    sval = sval + analogRead(z);// sensor on analog pin 'z'
  }
  sval = sval / 5.0;    // average
  return sval;
}


void setup() {
  Serial.begin(9600);
  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}


void loop() {
  float temp;
  temp = Thermistor(sample(ThermistorPIN));     // read ADC and  convert it to Celsius
  Serial.print("Celsius: ");
  Serial.print(temp, 1);
  float temperature;
  temperature = temp;
  
  temp = (temp * 9.0) / 5.0 + 32.0;                 // converts to  Fahrenheit
  Serial.print(", Fahrenheit: ");
  Serial.print(temp, 1);                            // display  Fahrenheit
  Serial.println("");
  
  // if the current temperature is lower than the baseline turn off all LEDs
  if (temperature < baselineTemp + 2) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } // if the temperature rises 2-4 degrees, turn an LED on
  else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } // if the temperature rises 4-6 degrees, turn a second LED on
  else if (temperature >= baselineTemp + 6 && temperature < baselineTemp + 10) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } // if the temperature rises more than 6 degrees, turn all LEDs on
  else if (temperature >= baselineTemp + 12) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  
  delay(1000);                                      // Delay a bit...
}
