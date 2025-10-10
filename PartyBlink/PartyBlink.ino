/*
  PARTY BLINK
  Igor Kochanski
*/

//Time between colours
  int ms = 500;
  
void setup() {
  Serial.begin(115200);
}

//RGB LEDs are Low-Active (LOW=ON, HIGH=OFF)
void loop() {
  //WHITE
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  delay(ms);
  //CYAN
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  delay(ms);
  //BLUE
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
  delay(ms);
  //MAGENTA
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
  delay(ms);
  //RED
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  delay(ms);
  //YELLOW
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
  delay(ms);
  //GREEN
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
  delay(ms);
  //OFF
  //digitalWrite(LEDR, HIGH);
  //digitalWrite(LEDG, HIGH);
  //digitalWrite(LEDB, HIGH);
  //delay(ms);
}
