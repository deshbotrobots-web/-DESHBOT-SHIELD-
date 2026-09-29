/*
============================================================
        DESHBOT ROBOTIC SHIELD - DEMO CODE
============================================================

Author: Deshraj Dhiman

Description:

This program demonstrates basic robot control using the
Deshbot Robotic Shield. The robot is controlled via
Serial commands (Bluetooth / USB), and movement status
is displayed on a 16x2 LCD.

------------------------------------------------------------
HARDWARE USED
------------------------------------------------------------

1. Arduino NANO
2. Deshbot Robotic Shield
3. 16x2 LCD Display
4. L293D Motor Driver
5. 4 DC Motors
6. Bluetooth Module (HC-05) / Serial Input

------------------------------------------------------------
PIN CONFIGURATION
------------------------------------------------------------

LCD:

RS -> A4
EN -> A3
D4 -> A2
D5 -> A1
D6 -> A0
D7 -> 13

Motor 1:

Motor_1a -> Pin 8
Motor_1b -> Pin 9

Motor 2:

Motor_2a -> Pin 6
Motor_2b -> Pin 7

------------------------------------------------------------
CONTROL COMMANDS
------------------------------------------------------------

U -> Move Forward
D -> Move Backward
L -> Turn Left
R -> Turn Right
C -> Stop Robot

============================================================
*/

#include <LiquidCrystal.h>


// ==========================================================
// LCD CONFIGURATION
// ==========================================================

const int rs = A4;
const int en = A3;
const int d4 = A2;
const int d5 = A1;
const int d6 = A0;
const int d7 = 13;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// ==========================================================
// SERIAL DATA
// ==========================================================

byte datarx;


// ==========================================================
// MOTOR CONTROL PINS
// ==========================================================

int Motor_1a = 8;
int Motor_1b = 9;

int Motor_2a = 6;
int Motor_2b = 7;


// ==========================================================
// SETUP
// ==========================================================

void setup()
{

    Serial.begin(9600);

    lcd.begin(16, 2);

    lcd.setCursor(0, 0);

    lcd.print(" Deshbot Robot ");


    pinMode(Motor_1a, OUTPUT);
    pinMode(Motor_1b, OUTPUT);

    pinMode(Motor_2a, OUTPUT);
    pinMode(Motor_2b, OUTPUT);


    Serial.println(F("=================================================="));

    Serial.println(F("       DESHBOT ROBOTIC SHIELD"));

    Serial.println(F("              QUICK REFERENCE"));

    Serial.println(F("=================================================="));

    Serial.println(F("Commands:"));

    Serial.println(F("  U = Forward"));
    Serial.println(F("  D = Backward"));
    Serial.println(F("  L = Left"));
    Serial.println(F("  R = Right"));
    Serial.println(F("  C = Stop"));

    Serial.println();

    Serial.println(F("Shield Pin Reference:"));

    Serial.println(
        F("Motors : Motor_1a=8 Motor_1b=9 Motor_2a=6 Motor_2b=7")
    );

    Serial.println(
        F("LCD    : RS=A4 EN=A3 D4=A2 D5=A1 D6=A0 D7=13")
    );

    Serial.println(
        F("Buzzer/LED/WS2812B : Pin 11")
    );

    Serial.println(
        F("Switches : SW1=10 SW2=12")
    );

    Serial.println(
        F("Ultrasonic : Trig=4 Echo=5")
    );

    Serial.println(F("=================================================="));

}


// ==========================================================
// MAIN LOOP
// ==========================================================

void loop()
{

    if (Serial.available() > 0)
    {

        datarx = Serial.read();

        Serial.println(datarx);

    }


    //--------------------------------------------------------
    // FORWARD
    //--------------------------------------------------------

    if (datarx == 'U')
    {

        lcd.setCursor(0, 1);

        lcd.print(" Moving Forward ");

        digitalWrite(Motor_1a, HIGH);
        digitalWrite(Motor_1b, LOW);

        digitalWrite(Motor_2a, LOW);
        digitalWrite(Motor_2b, HIGH);

    }


    //--------------------------------------------------------
    // BACKWARD
    //--------------------------------------------------------

    if (datarx == 'D')
    {

        lcd.setCursor(0, 1);

        lcd.print("Moving Backward");

        digitalWrite(Motor_1a, LOW);
        digitalWrite(Motor_1b, HIGH);

        digitalWrite(Motor_2a, HIGH);
        digitalWrite(Motor_2b, LOW);

    }


    //--------------------------------------------------------
    // LEFT
    //--------------------------------------------------------

    if (datarx == 'L')
    {

        lcd.setCursor(0, 1);

        lcd.print("  Moving Left  ");

        digitalWrite(Motor_1a, HIGH);
        digitalWrite(Motor_1b, LOW);

        digitalWrite(Motor_2a, LOW);
        digitalWrite(Motor_2b, LOW);

    }


    //--------------------------------------------------------
    // RIGHT
    //--------------------------------------------------------

    if (datarx == 'R')
    {

        lcd.setCursor(0, 1);

        lcd.print(" Moving Right  ");

        digitalWrite(Motor_1a, LOW);
        digitalWrite(Motor_1b, LOW);

        digitalWrite(Motor_2a, LOW);
        digitalWrite(Motor_2b, HIGH);

    }


    //--------------------------------------------------------
    // STOP
    //--------------------------------------------------------

    if (datarx == 'C')
    {

        lcd.setCursor(0, 1);

        lcd.print(" Robot Stopped ");

        digitalWrite(Motor_1a, LOW);
        digitalWrite(Motor_1b, LOW);

        digitalWrite(Motor_2a, LOW);
        digitalWrite(Motor_2b, LOW);

    }

}


/*
============================================================
                    NOTES FOR STUDENTS
============================================================

• Motors are controlled using HIGH/LOW logic.

• LCD provides real-time movement feedback.

• Serial commands can come from:
    - Bluetooth App
    - Serial Monitor

• This is a basic differential-drive robot.

------------------------------------------------------------
EXTENSIONS
------------------------------------------------------------

• Add obstacle sensors
• Add autonomous navigation
• Add ultrasonic sensors
• Integrate mobile app control
• Add line-following functionality
• Add Wi-Fi / IoT control

============================================================
                 HAPPY DESHBOT CODING 🚀
============================================================
*/