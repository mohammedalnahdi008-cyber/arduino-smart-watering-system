🌱 arduino-smart-watering-system

Automated watering system built with Arduino, an HC-SR04 ultrasonic sensor, a relay module, and an electric water pump.

The system controls water flow efficiently by activating the pump through a serial command and stopping it automatically once the water level drops by approximately 3 cm.

🔍 Overview

This project uses an ultrasonic sensor to monitor water level while a pump is running. When the system receives the ON command through the Arduino Serial Monitor, it activates the pump and records the starting distance from the sensor to the water surface.

As the pump drains water, the measured distance increases. Once the distance increases by 3 cm from the starting point, the system automatically turns the pump off.

⚙️ Features
Serial-controlled pump activation
Water level measurement using HC-SR04
Automatic shutoff after ~3 cm level drop
Relay-controlled pump switching
Basic sensor-error safety behavior
Real-time feedback via Serial Monitor

🧰 Components Used
Arduino Uno
HC-SR04 ultrasonic sensor
Electric water pump
Relay module
Breadboard
Jumper wires (male-male, male-female, female-female)
USB connection (Arduino powered via laptop)

🧠 How It Works
The system starts with the pump off
The ultrasonic sensor continuously measures distance to the water surface
When ON is entered in the Serial Monitor, the pump activates
The initial water level (distance) is stored
While running, the system keeps measuring distance
If the distance increases by 3 cm, the pump stops automatically
If invalid sensor readings occur, the pump is stopped as a safety measure

💻 Code Logic
A continuous loop reads sensor data and listens for serial input
measureDistance() calculates distance using ultrasonic echo timing
Pump state is tracked using a boolean variable (pumpActive)

Stop condition:

if (distance >= startDistance + stopDelta) {
  digitalWrite(relayPin, HIGH); // Pump OFF
  pumpActive = false;
}
stopDelta is set to 3.0

🔌 Pin Configuration
HC-SR04 Trigger → Pin 5
HC-SR04 Echo → Pin 6
Relay Module → Pin 2

▶️ Usage
Connect all components to the Arduino
Upload the code
Open Serial Monitor (9600 baud)
Type ON and press enter
The pump will run and stop automatically based on water level change
📸 Photos




📝 Notes

This project focuses on simple sensing, control logic, and efficient water usage through automatic pump shutoff.

🚀 Possible Improvements
Add a soil moisture sensor for plant-based decisions
Add a manual OFF command
Use an external power supply for the pump
Add a display (LCD/OLED) for live readings
Build an enclosure for better structure

📄 License
Open for learning and educational use.
