/*
  Thermometer
  Igor Kochanski
*/

// Arduino Nano 33 BLE Sense Rev2

#include <Arduino_LPS22HB.h>
#include <Arduino_HS300x.h>

const float cold   = 8.0;  // Blue
const float chilly = 14.0; // Cyan
const float comfy  = 20.0; // Green
const float warm   = 26,0; // Yellow
const float hot    = 32.0; // Red





void setRGB(int r, int g, int b) {
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);

  // Invert values - LED is active-LOW
  analogWrite(LEDR, 255 - r);
  analogWrite(LEDG, 255 - g);
  analogWrite(LEDB, 255 - b);
}

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  Serial.begin(9600);
  while (!Serial);

  // LPS22HB - Read Pressure & Temperature
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while(1);
  }
  //HS3003 - Read Humidity & Temperature
  if (!HS300x.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while(1);
  }
}

void loop() {
  // read sensor values
  float humidity     = HS300x.readHumidity();
  float temperature1 = HS300x.readTemperature();
  float temperature2 = BARO.readTemperature();
  float avgTemp      = (temperature1+temperature2)/2;
  float pressure     = BARO.readPressure();
  float r, g, b;



  // print sensor values
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.print("%");

  Serial.print(" Pressure = ");
  Serial.print(pressure);
  Serial.print("kPA");

  Serial.print(" Temp1 = ");
  Serial.print(temperature1);
  Serial.print("°C");

  Serial.print(" Temp2 = ");
  Serial.print(temperature2);
  Serial.print("°C");
  
  Serial.print(" AVG.(");
  Serial.print(avgTemp);
  Serial.print(")");

  Serial.println();

  // wait to print again
  delay(1000);
}



setRGB(0, 0, 255);