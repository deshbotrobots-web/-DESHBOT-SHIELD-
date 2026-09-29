#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// LCD
LiquidCrystal lcd(A4, A3, A2, A1, A0, 13);

// GPS
// Arduino RX = D5  <- NEO-6M TX
// Arduino TX = D4  -> NEO-6M RX
SoftwareSerial gpsSerial(5, 4);

String gpsData = "";

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("GPS Starting...");
  lcd.setCursor(0, 1);
  lcd.print("Wait Signal...");
}

void loop() {

  while (gpsSerial.available()) {

    char c = gpsSerial.read();

    // Print raw GPS data to Serial Monitor
    Serial.write(c);

    // New GPS sentence starts with $
    if (c == '$') {
      gpsData = "";
    }

    gpsData += c;

    // Sentence ends
    if (c == '\n') {

      // Check for GPGGA sentence
      if (gpsData.indexOf("$GPGGA") >= 0 ||
          gpsData.indexOf("$GNGGA") >= 0) {

        showGPS();
      }
    }
  }
}

void showGPS() {

  // Split the GPGGA sentence
  // Example:
  // $GPGGA,123519,4807.038,N,01131.000,E,...

  int comma1 = gpsData.indexOf(',');
  int comma2 = gpsData.indexOf(',', comma1 + 1);
  int comma3 = gpsData.indexOf(',', comma2 + 1);
  int comma4 = gpsData.indexOf(',', comma3 + 1);
  int comma5 = gpsData.indexOf(',', comma4 + 1);
  int comma6 = gpsData.indexOf(',', comma5 + 1);

  String latitude = gpsData.substring(comma2 + 1, comma3);
  String northSouth = gpsData.substring(comma3 + 1, comma4);

  String longitude = gpsData.substring(comma4 + 1, comma5);
  String eastWest = gpsData.substring(comma5 + 1, comma6);

  lcd.clear();

  // Line 1
  lcd.setCursor(0, 0);
  lcd.print("LAT:");
  lcd.print(latitude);

  // Line 2
  lcd.setCursor(0, 1);
  lcd.print("LON:");
  lcd.print(longitude);

  Serial.println();
  Serial.print("Latitude: ");
  Serial.print(latitude);
  Serial.print(" ");
  Serial.println(northSouth);

  Serial.print("Longitude: ");
  Serial.print(longitude);
  Serial.print(" ");
  Serial.println(eastWest);
}