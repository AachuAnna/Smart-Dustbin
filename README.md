# Smart Dustbin 🚮 

An Arduino-based smart dustbin that automatically opens its lid when a hand is detected using an ultrasonic sensor.

## Features
- Touchless operation
- Automatic lid opening using servo motor
- Buzzer feedback
- Green/Red LED status indication
- Hygienic and user-friendly design

## Components Used
- Arduino UNO
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- Buzzer
- Red & Green LEDs
- Resistors
- Breadboard & Jumper wires

## Working Principle
The ultrasonic sensor measures the distance to an object.  
When a hand is detected within 15 cm, the servo motor opens the dustbin lid, activates the green LED, and triggers a buzzer.  
If no object is detected, the lid remains closed and the red LED stays ON.

## Author
Aachu Anna Sony
