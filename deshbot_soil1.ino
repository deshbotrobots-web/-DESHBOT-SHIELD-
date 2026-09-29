#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial GPS(5, 4); // Nano RX = D5, TX = D4

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(A4, A3, A2, A1, A0, 13);

String gpsData = "";

void setup() {

  Serial.begin(9600);
  GPS.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("GPS: NO FIX");

  lcd.setCursor(0, 1);
  lcd.print("SAT: 0");
}

void loop() {

  while (GPS.available()) {

    char c = GPS.read();

    // Show RAW GPS data on Serial Monitor
    Serial.write(c);

    if (c == '\n') {

      // Process GPGGA sentence for LCD
      if (gpsData.startsWith("$GPGGA")) {

        int comma[10];
        int count = 0;

        for (int i = 0; i < gpsData.length(); i++) {

          if (gpsData[i] == ',' && count < 10) {
            comma[count++] = i;
          }
        }

        if (count >= 7) {

          // GPS fix status
          String fix = gpsData.substring(comma[5] + 1, comma[6]);

          // Number of satellites
          String sat = gpsData.substring(comma[6] + 1, comma[7]);

          // LCD line 1
          lcd.setCursor(0, 0);

          if (fix == "1" || fix == "2") {
            lcd.print("GPS: FIX OK     ");
          } 
          else {
            lcd.print("GPS: NO FIX     ");
          }

          // LCD line 2
          lcd.setCursor(0, 1);
          lcd.print("SAT: ");
          lcd.print(sat);
          lcd.print("           ");
        }
      }

      gpsData = "";
    }

    else if (c != '\r') {
      gpsData += c;
    }
  }
}