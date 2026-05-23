#include <Arduino_BMI270_BMM150.h>

// Classic Magic 8-Ball responses
const char* responses[] = {
  "It is certain",
  "Without a doubt",
  "You may rely on it",
  "Yes, definitely",
  "Most likely",
  "Reply hazy, try again",
  "Ask again later",
  "Better not tell you now",
  "Cannot predict now",
  "Don't count on it",
  "My reply is no",
  "My sources say no",
  "Outlook not so good",
  "Very doubtful"
};

const int numResponses = sizeof(responses) / sizeof(responses[0]);

// Shake detection parameters
const float SHAKE_THRESHOLD = 2.5; // G-force threshold (1.0 is sitting still)
unsigned long lastShakeTime = 0;
const unsigned long COOLDOWN_MS = 2000; // Prevent accidental double-triggering

void setRGB(int r, int g, int b) {
  // Invert values - LED is active-LOW
  analogWrite(LEDR, 255 - r);
  analogWrite(LEDG, 255 - g);
  analogWrite(LEDB, 255 - b);
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor to open

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  if (!IMU.begin()) {
    Serial.println("[BMI270_BMM150] Failed to initialize IMU sensor!");
    while (1);
  }

  Serial.println("Magic 8-Ball Ready! Ask a question and shake...");
  
  // Seed the random generator using noise from an unused analog pin
  randomSeed(analogRead(A0));
  setRGB(0, 0, 0);
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Calculate the total G-force
    float totalAcceleration = sqrt(x * x + y * y + z * z);

    // Check if the acceleration exceeds threshold and cooldown passed
    if (totalAcceleration > SHAKE_THRESHOLD && (millis() - lastShakeTime > COOLDOWN_MS)) {
      lastShakeTime = millis();
      
      // Flash the onboard LED to show it detected the shake
      for(int i = 0; i < 3; i++) {
        delay(100);
        setRGB(128, 0, 128); // purple
        delay(100);
        setRGB(0, 0, 0);
      }

      // Pick and display a random response
      int randomIndex = random(numResponses);
      Serial.println(responses[randomIndex]);
    }
  }
}