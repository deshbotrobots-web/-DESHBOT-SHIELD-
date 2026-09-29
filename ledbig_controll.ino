#define LED 11
#define POT A0

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {

  // Read potentiometer
  int potValue = analogRead(POT);

  // Convert 0-1023 to 0-255
  int brightness = map(potValue, 0, 1023, 0, 255);

  // Set LED brightness
  analogWrite(LED, brightness);

  delay(10);
}