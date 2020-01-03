/*
   Inputs ADC Value from VMA320 Thermistor and outputs Temperature in Celsius

   Utilizes the Steinhart-Hart Thermistor Equation:
      Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
      where A = 0.001129148, B = 0.000234125 and C = 8.76741E-08

   These coefficients seem to work fairly universally, which is a bit of a
   surprise.

   Schematic:
     [Ground] -- [10k-pad-resistor] -- | -- [thermistor] --[Vcc (5 or 3.3v)]
                                                 |
                                            Analog Pin 0

   In case it isn't obvious (as it wasn't to me until I thought about it), the analog ports
   measure the voltage between 0v -> Vcc which for an Arduino is a nominal 5v

   The resistance calculation uses the ratio of the two resistors, so the voltage
   specified above is really only required for the debugging that is commented out below

   Resistance = PadResistor * (1024/ADC -1)

   For a GND-Thermistor-PullUp--Varef circuit it would be Rtherm=Rpullup/(1024.0/ADC-1)
   The VMA320 is pull-up
*/

#include <Arduino.h>

#include <math.h>

#define ThermistorPIN 0
// Analog Pin 0

float vcc = 5.00;
// only used for display purposes, if used
// set to the measured Vcc.
float pad = 10000;
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
  Serial.print("/1024");
  Serial.print(", vcc: ");
  Serial.print(vcc, 1);
  Serial.print(", pad: ");
  Serial.print(pad / 1000, 0);
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
}

void loop() {
  float temp;
  temp = Thermistor(sample(ThermistorPIN));     // read ADC and  convert it to Celsius
  Serial.print("Celsius: ");
  Serial.print(temp, 1);                            // display Celsius
  temp = (temp * 9.0) / 5.0 + 32.0;                 // converts to  Fahrenheit
  Serial.print(", Fahrenheit: ");
  Serial.print(temp, 1);                            // display  Fahrenheit
  Serial.println("");
  delay(5000);                                      // Delay a bit...
}
