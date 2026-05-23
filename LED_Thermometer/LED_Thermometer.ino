/*
  LED_Thermometer
  Igor Kochanski
*/

// Arduino Nano 33 BLE Sense Rev2

#include <Arduino_LPS22HB.h>
#include <Arduino_HS300x.h>

const float cold   = 20; // Blue
const float comfy  = 25; // Green
const float hot    = 30; // Red
int r, g, b;

void setRGB(int r, int g, int b) {
  // Invert values - LED is active-LOW
  analogWrite(LEDR, 255 - r);
  analogWrite(LEDG, 255 - g);
  analogWrite(LEDB, 255 - b);
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setColor(float temp) {
  // BLUE
  if (temp <= cold) {
    r = 0; g = 0; b = 255;
  } 
  // BLUE -> GREEN
  else if (temp < comfy) {
    r = 0;
    g = mapf(temp, cold, comfy, 0, 255);
    b = mapf(temp, cold, comfy, 255, 0);
  } 
  // GREEN -> RED
  else if (temp < hot) {
    b = 0;
    r = mapf(temp, comfy, hot, 0, 255);
    g = mapf(temp, comfy, hot, 255, 0);
    
  } 
  // RED
  else {
    r = 255; g = 0; b = 0;
  }
  setRGB(r, g, b);
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
  float temperature1 = HS300x.readTemperature();
  float temperature2 = BARO.readTemperature();
  float avgTemp  = (temperature1+temperature2)/2;
  float pressure = BARO.readPressure()*10; // read pressure kPa and convert to hPa
  float humidity = HS300x.readHumidity();

  Serial.print(temperature1);
  Serial.print("°C | ");

  Serial.print(temperature2);
  Serial.print("°C | ");

  Serial.print("diff. ");
  Serial.print(temperature1 - temperature2);
  Serial.print("°C | ");
  
  Serial.print("avg. ");
  Serial.print(avgTemp);
  Serial.print("°C | ");

  Serial.print(r);
  Serial.print(", ");
  Serial.print(g);
  Serial.print(", ");
  Serial.print(b);
  Serial.print(" | ");

  Serial.print(humidity);
  Serial.print("% | ");

  Serial.print(pressure);
  Serial.print("hPa");

  Serial.println();

  setColor(avgTemp);

  // wait to print again
  delay(1000);
}