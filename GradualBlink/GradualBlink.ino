/*
  Gradiant BLINK
  Igor Kochanski
*/

// Arduino Nano 33 BLE Sense Rev2
// Gradually fades through colors on the onboard RGB LED

int r = 255, g = 0, b = 0;   // Start with red
int stage = 0;               // Current color transition

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop() {
  // Update color gradually
  switch (stage) {
    case 0: g++; if (g >= 255) stage++; break;   // Red → Yellow → Green
    case 1: r--; if (r <= 0) stage++; break;     // Green
    case 2: b++; if (b >= 255) stage++; break;   // Green → Cyan → Blue
    case 3: g--; if (g <= 0) stage++; break;     // Blue
    case 4: r++; if (r >= 255) stage++; break;   // Blue → Magenta → Red
    case 5: b--; if (b <= 0) stage = 0; break;   // Red again
  }
  // The onboard RGB LED is *active low* (0 = ON)
  analogWrite(LEDR,   255 - r);
  analogWrite(LEDG, 255 - g);
  analogWrite(LEDB,  255 - b);

  delay(10);
}


