#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- PINS ----------------

#define DHT_PIN 9
#define DHT_TYPE DHT11

#define MOTOR_A 6
#define MOTOR_B 7

DHT dht(DHT_PIN, DHT_TYPE);

// ---------------- VARIABLES ----------------

float temperature;
float humidity;

void fanOff() {
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
}

void fanOn() {
  digitalWrite(MOTOR_A, HIGH);
  digitalWrite(MOTOR_B, LOW);
}

void setup() {

  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);

  fanOff();

  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(15, 20);
  display.println("SMART FAN");

  display.display();

  delay(2000);
}

void loop() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {

    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("DHT ERROR");

    display.display();

    fanOff();

    delay(2000);
    return;
  }

  display.clearDisplay();

  // Temperature
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temperature: ");

  display.setTextSize(2);
  display.setCursor(0, 12);
  display.print(temperature, 1);
  display.print(" C");

  // Humidity
  display.setTextSize(1);
  display.setCursor(0, 38);
  display.print("Humidity: ");
  display.print(humidity, 0);
  display.print("%");

  // Fan control
  display.setCursor(0, 52);

  if (temperature < 25) {

    fanOff();

    display.print("FAN: OFF");
  }

  else if (temperature < 28) {

    fanOn();

    display.print("FAN: LOW");
  }

  else if (temperature < 31) {

    fanOn();

    display.print("FAN: MEDIUM");
  }

  else {

    fanOn();

    display.print("FAN: HIGH");
  }

  display.display();

  delay(2000);
}