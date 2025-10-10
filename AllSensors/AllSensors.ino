/*
  All Sensors
  Igor Kochanski
*/

// Arduino Nano 33 BLE Sense Rev2

#include <Arduino_LPS22HB.h>
#include <Arduino_HS300x.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");
  
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

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  // read sensor values
  float humidity     = HS300x.readHumidity();
  float temperature1 = HS300x.readTemperature();
  float temperature2 = BARO.readTemperature();
  float pressure     = BARO.readPressure();
  float x, y, z;

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
  Serial.print((temperature1+temperature2)/2);
  Serial.print(")");

  Serial.println();

  // wait to print again
  delay(1000);
}
