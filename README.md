# Deshbot Shield Projects

A collection of practical electronics, Arduino, embedded systems, IoT, robotics, and automation projects built using the **Deshbot Shield**.

The Deshbot Shield is designed to make electronics learning easier by providing commonly used components and interfaces on a single development platform. Students can use the shield with Arduino boards such as the **Arduino Uno and Arduino Nano** to build and experiment with practical projects.

---

## Features

* Easy-to-use electronics development platform
* Compatible with Arduino Uno/Nano based projects
* Supports sensors, displays, buttons, motors, buzzers and other modules
* Designed for practical Electronics and Embedded Systems learning
* Suitable for Robotics, IoT and Automation projects
* Projects can be modified and expanded according to the student's requirements

---

# Hardware

The Deshbot Shield can be used with different electronic components and modules.

| Component         | Purpose                  | Interface / Pin  |
| ----------------- | ------------------------ | ---------------- |
| Arduino Uno/Nano  | Main controller          | Digital / Analog |
| OLED Display      | Display information      | I2C              |
| 16×2 LCD          | Text display             | Digital          |
| Ultrasonic Sensor | Distance measurement     | Digital          |
| IR Sensor         | Object/speed detection   | Digital          |
| DHT11             | Temperature & humidity   | Digital          |
| Buzzer            | Sound indication         | Digital          |
| Push Buttons      | User input               | Digital          |
| RGB LED           | Status indication        | Digital          |
| Motor Driver      | Motor control            | Digital          |
| DC Motor          | Movement / mechanism     | Motor Driver     |
| Water Pump        | Water spraying / pumping | Motor Driver     |
| Flame Sensor      | Fire/flame detection     | Digital          |
| Bluetooth Module  | Wireless communication   | Serial           |
| GPS Module        | Location tracking        | Serial           |

> **Note:** Exact pin assignments may vary depending on the Deshbot Shield version and the project.

---

# Common Deshbot Shield Pin Configuration

The following pins are commonly used in the Deshbot Shield projects.

```text
OLED SDA ........ A4
OLED SCL ........ A5

Motor Driver A .. D6
Motor Driver B .. D7

Buzzer .......... D11

Button .......... D10
Button .......... D12

IR Sensor ....... D9

DHT11 ........... D9

RGB LED ......... D11

Ultrasonic TRIG . A0 / A3
Ultrasonic ECHO . 13 / A4
```

> Always check the individual project wiring before connecting components, because some projects use the same pins for different modules.

---

# Project Collection

## 1. OLED Parking Sensor

### Description

An ultrasonic sensor detects the distance between the vehicle/object and the parking area. The OLED displays the measured distance and the buzzer provides an alert when the object gets close.

### Components

* Arduino Uno/Nano
* OLED display
* Ultrasonic sensor
* Buzzer
* Deshbot Shield

### Working

```text
Ultrasonic Sensor
        │
        ▼
   Arduino
        │
   ┌────┴────┐
   ▼         ▼
 OLED      Buzzer
Display     Alert
```

---

# 2. IR Speed Meter

### Description

An IR sensor detects an object passing through a measurement point and calculates its speed.

### Components

* Arduino
* IR sensor
* OLED / LCD
* Deshbot Shield

### Output

```text
Object Detected
      ↓
Measure Time
      ↓
Calculate Speed
      ↓
Display Speed
```

---

# 3. Ultrasonic Distance Meter

### Description

Measures the distance of an object using an ultrasonic sensor and displays the result on an OLED.

### Example Output

```text
DISTANCE

  24 cm
```

---

# 4. Traffic Light System

### Description

A programmable traffic-light system using LEDs.

The Arduino controls the traffic lights according to a fixed sequence.

### Example Sequence

```text
RED
 ↓
GREEN
 ↓
YELLOW
 ↓
RED
```

The timing can be changed in the Arduino program.

---

# 5. Traffic Light Quiz System

### Description

A quiz-based project that combines an OLED display, buttons and traffic-light indicators.

The OLED displays a question and the user selects an answer using buttons.

### Result

```text
Correct Answer
      ↓
GREEN

Wrong Answer
      ↓
RED
```

This project demonstrates:

* User input
* Conditional statements
* OLED display
* LED control
* Basic embedded programming

---

# 6. Elevator Controller

### Description

A simple elevator simulation using buttons, OLED display and a motor.

The user selects the required direction or floor and the motor simulates elevator movement.

### Components

* Arduino
* OLED
* Push buttons
* Motor driver
* DC motor
* Buzzer

### Basic Flow

```text
Button Press
     ↓
Read Selection
     ↓
Start Motor
     ↓
Move Elevator
     ↓
Stop Motor
     ↓
Display Floor
```

---

# 7. Automatic Gate

### Description

An ultrasonic sensor detects an approaching object and automatically controls a motor to open or close a gate.

### Working

```text
Object Detected
      ↓
Ultrasonic Sensor
      ↓
Arduino
      ↓
Motor Driver
      ↓
Gate Opens
```

An RGB LED can also be used to indicate the gate status.

---

# 8. Flame Detection & Water Pump

### Description

A flame sensor detects a fire/flame condition. When a flame is detected, the Arduino activates a water pump.

An ultrasonic sensor can be used to detect the distance from the fire/object and stop or control the system according to the programmed conditions.

### Working

```text
Flame Sensor
     │
     ▼
  Arduino
     │
     ▼
Water Pump
     │
     ▼
Water Spray
```

---

# 9. Automatic Fan Using DHT11

### Description

The DHT11 measures temperature and humidity. The Arduino controls a motor/fan according to the temperature.

### Example

```text
Temperature < Set Value
        ↓
Fan OFF

Temperature > Set Value
        ↓
Fan ON
```

---

# 10. Temperature & Humidity Monitor

### Description

A DHT11 sensor measures temperature and humidity and displays the readings on an OLED.

### Example Output

```text
TEMP: 28 C
HUM : 62 %
```

This project demonstrates sensor reading and display control.

---

# 11. Bluetooth Remote Control

### Description

A Bluetooth module can be connected to the Arduino to receive commands from a phone or another Bluetooth device.

The received commands can control:

* Motors
* Pumps
* LEDs
* Buzzers
* Other outputs

### Example

```text
Phone
  │
Bluetooth
  │
  ▼
Arduino
  │
  ├── Motor
  ├── Pump
  └── LED
```

---

# 12. Bluetooth Pump Controller

### Description

A Bluetooth module is used to remotely control a water pump.

### Example Commands

```text
1 → Pump ON
0 → Pump OFF
```

The Arduino receives the command through serial communication and controls the motor driver.

---

# 13. Bluetooth Robot

### Description

A Bluetooth-controlled robot can be operated using commands received from a phone.

### Example Controls

```text
F → Forward
B → Backward
L → Left
R → Right
S → Stop
```

The Arduino converts the received commands into motor-driver signals.

---

# 14. Obstacle Avoiding Robot

### Description

An ultrasonic sensor detects obstacles in front of the robot.

When an obstacle is detected, the Arduino stops or changes the robot's direction.

### Working

```text
Ultrasonic Sensor
       ↓
Obstacle Detected?
       │
   ┌───┴───┐
  NO      YES
   │        │
   ▼        ▼
Forward    Stop
            ↓
        Change Direction
```

---

# 15. Fire-Fighting Robot

### Description

A robot combines an ultrasonic sensor, flame sensor and water pump.

The robot searches for an obstacle/fire location, detects the flame and activates the pump.

### System

```text
        ┌──────────────┐
        │    Arduino   │
        └──────┬───────┘
               │
      ┌────────┼────────┐
      ▼        ▼        ▼
 Ultrasonic  Flame     Motor
  Sensor     Sensor    Driver
                         │
                         ▼
                       Robot

Flame Detected
      ↓
   Pump ON
      ↓
 Water Spray
```

---

# 16. OLED Alarm Clock

### Description

An OLED-based alarm clock using buttons for setting the alarm.

The buzzer activates when the programmed alarm time is reached.

### Controls

```text
D10 → Set / Increase
D12 → Stop / Control
D11 → Buzzer
```

---

# 17. OLED Mini OS

### Description

A small menu-based interface displayed on an OLED.

The user can navigate through different functions using buttons.

### Example Menu

```text
DESHBOT OS

> Sensor
  Motor
  Alarm
  Settings
```

This project demonstrates:

* Menus
* Functions
* Button input
* OLED graphics
* State management

---

# 18. OLED Pong Game

### Description

A simple Pong-style game displayed on a 128×64 OLED.

Buttons are used to control the paddle.

### Features

* Player paddle
* Moving ball
* Collision detection
* Score
* Game-over condition

---

# 19. Whack-a-Mole Game

### Description

An interactive reaction game using buttons and an OLED.

The OLED displays a target and the player must press the correct button before the target changes.

### Demonstrates

* Random numbers
* Timers
* Buttons
* OLED graphics
* Game logic

---

# 20. Password Lock

### Description

A digital password system using buttons.

The user enters a password using the available buttons. The Arduino checks the entered sequence.

### Example

```text
ENTER PASSWORD

* * * *

Correct
  ↓
ACCESS GRANTED

Wrong
  ↓
ACCESS DENIED
```

---

# 21. Touch Alarm

### Description

A touch sensor is used to detect contact and activate an alarm.

The buzzer can be used as the alarm output while an OLED displays the system status.

---

# 22. GPS Location Project

### Description

A GPS module such as the NEO-6M can be connected to the Arduino to receive satellite location data.

The GPS can provide information such as:

* Latitude
* Longitude
* Time
* Satellite information

> **Important:** GPS modules generally need a clear view of the sky to receive satellite signals. Indoor testing may not provide a reliable GPS fix.

---

# 23. Dual Arduino Communication

### Description

Two Arduino boards can communicate with each other using serial communication.

One Arduino can act as the transmitter while the second Arduino acts as the receiver.

### Example

```text
Arduino 1
   │
   │ Serial
   ▼
Arduino 2
   │
   ├── OLED
   ├── LED
   └── Buzzer
```

---

# 24. Two-Player OLED Game

### Description

Two Arduino boards can communicate to create a multiplayer game.

Buttons are used as player controls and the OLED displays the game state.

This project introduces:

* Serial communication
* Data transmission
* Button input
* Game logic
* Multi-board systems

---

# Programming Concepts Covered

The Deshbot Shield projects are designed to progressively teach programming and electronics concepts.

### Beginner

* `pinMode()`
* `digitalWrite()`
* `digitalRead()`
* `analogRead()`
* Variables
* `if / else`
* `delay()`

### Intermediate

* Functions
* `switch / case`
* Arrays
* Timers
* Serial communication
* Sensor interfacing
* OLED graphics
* Motor control

### Advanced

* State machines
* Multiple sensors
* Bluetooth communication
* Multi-Arduino communication
* Robotics
* IoT
* Embedded system design

---

# Typical Arduino Project Structure

Most Deshbot Shield projects follow this structure:

```cpp
void setup() {

  // Initialize pins
  // Initialize sensors
  // Initialize display
  // Initialize Serial

}

void loop() {

  // Read sensors
  // Process data
  // Control outputs
  // Update display

}
```

---

# Recommended Project Development Flow

```text
1. Understand the Project
          ↓
2. Identify Components
          ↓
3. Check Pin Connections
          ↓
4. Connect Hardware
          ↓
5. Upload Arduino Code
          ↓
6. Test Individual Components
          ↓
7. Combine Components
          ↓
8. Test Complete Project
          ↓
9. Modify / Improve Project
```

---

# Arduino IDE

The projects can be programmed using the **Arduino IDE**.

### Basic Steps

1. Install Arduino IDE.
2. Connect the Arduino board.
3. Select the correct board.
4. Select the correct COM port.
5. Open the project code.
6. Install required libraries.
7. Verify/compile the code.
8. Upload the program.
9. Test the hardware.

---

# Required Libraries

Depending on the project, libraries may include:

```text
Wire.h
Adafruit_GFX.h
Adafruit_SSD1306.h
DHT.h
SoftwareSerial.h
Servo.h
```

Only install the libraries required by the individual project.

---

# Troubleshooting

| Problem                 | Possible Cause              | Solution                       |
| ----------------------- | --------------------------- | ------------------------------ |
| OLED not working        | Wrong I2C address           | Check OLED address and wiring  |
| Sensor not responding   | Incorrect wiring            | Check VCC, GND and signal pins |
| Motor not moving        | Motor driver connection     | Check driver inputs and power  |
| Pump not working        | Insufficient power          | Check motor/pump power supply  |
| Bluetooth not receiving | TX/RX problem               | Check serial wiring            |
| Arduino not detected    | USB/driver issue            | Check cable and COM port       |
| GPS no location         | Indoor environment          | Test outdoors with clear sky   |
| Buzzer always ON        | Logic/pin problem           | Check output condition         |
| Button not responding   | Wiring/pull-up issue        | Check button connection        |
| OLED shows garbage      | Wrong library/configuration | Check display initialization   |

---

# Safety Notes

* Check the operating voltage of every component before connecting it.
* Do not power motors or pumps directly from an Arduino GPIO pin.
* Use an appropriate motor driver for motors and pumps.
* Make sure all connected modules share the correct GND reference.
* Check polarity before connecting batteries or external power supplies.
* Use suitable power supplies for motors, pumps and other high-current devices.
* Disconnect power before changing hardware connections.

---

# Project Ideas

The Deshbot Shield can also be used as a starting point for larger projects:

* Smart Home Automation
* Smart Parking
* Fire Fighting Robot
* Bluetooth Robot
* Automatic Watering System
* Temperature-Controlled Fan
* Smart Door/Gate
* IoT Sensor Station
* GPS Tracker
* Security Alarm
* Digital Door Lock
* Mini Weather Station
* Obstacle Avoiding Robot
* Line Following Robot
* Sensor Monitoring System

---

# Learning Path

A recommended learning path is:

```text
LED & Buzzer
      ↓
Buttons
      ↓
Sensors
      ↓
OLED Display
      ↓
Motors
      ↓
Motor Driver
      ↓
Multiple Sensors
      ↓
Bluetooth
      ↓
Robotics
      ↓
IoT & Automation
```

---

# Project Files

A typical Deshbot Shield project repository can be organized as:

```text
Deshbot-Shield-Projects/
│
├── README.md
│
├── 01_Basic_LED/
│   └── 01_Basic_LED.ino
│
├── 02_Button_Buzzer/
│   └── 02_Button_Buzzer.ino
│
├── 03_OLED_Display/
│   └── 03_OLED_Display.ino
│
├── 04_Ultrasonic_Distance/
│   └── 04_Ultrasonic_Distance.ino
│
├── 05_IR_Speed_Meter/
│   └── 05_IR_Speed_Meter.ino
│
├── 06_Temperature_Humidity/
│   └── 06_Temperature_Humidity.ino
│
├── 07_Traffic_Light/
│   └── 07_Traffic_Light.ino
│
├── 08_Automatic_Gate/
│   └── 08_Automatic_Gate.ino
│
├── 09_Fire_Fighting/
│   └── 09_Fire_Fighting.ino
│
├── 10_Bluetooth_Control/
│   └── 10_Bluetooth_Control.ino
│
└── images/
    └── project_images/
```

---

# About Deshbot

**Deshbot** develops practical electronics and learning solutions for students interested in:

* Electronics
* Embedded Systems
* IoT
* Robotics
* Automation
* Programming

The Deshbot Shield provides a practical platform where students can learn by building real working projects.

---

## License

This project collection is intended for educational and development purposes.

Refer to the individual project files for project-specific code, libraries, hardware requirements and usage information.
