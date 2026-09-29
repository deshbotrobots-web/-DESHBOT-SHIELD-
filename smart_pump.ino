#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11
#define DHT_PIN 9
#define DHT_TYPE DHT11

// Water Pump Motor Driver
#define PUMP_A 6
#define PUMP_B 7

DHT dht(DHT_PIN, DHT_TYPE);

float temperature;
float humidity;

void setup() {

  pinMode(PUMP_A, OUTPUT);
  pinMode(PUMP_B, OUTPUT);

  // Pump OFF
  digitalWrite(PUMP_A, LOW);
  digitalWrite(PUMP_B, LOW);

  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(15, 20);
  display.println("HOT WATER");

  display.display();

  delay(2000);
}

void loop() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // DHT error
  if (isnan(temperature) || isnan(humidity)) {

    digitalWrite(PUMP_A, LOW);
    digitalWrite(PUMP_B, LOW);

    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(20, 20);
    display.println("DHT ERROR");

    display.display();

    delay(2000);
    return;
  }

  display.clearDisplay();

  // Temperature
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temperature:");

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

  // Pump control
  display.setCursor(0, 52);

  if (temperature < 20) {

    // Pump ON
    digitalWrite(PUMP_A, HIGH);
    digitalWrite(PUMP_B, LOW);

    display.print("PUMP: ON");

  } 
  else {

    // Pump OFF
    digitalWrite(PUMP_A, LOW);
    digitalWrite(PUMP_B, LOW);

    display.print("PUMP: OFF");
  }

  display.display();

  delay(2000);
}