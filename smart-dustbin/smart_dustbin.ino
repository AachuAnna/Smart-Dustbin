#include <Servo.h>

// -------- Pin Definitions --------
const int trigPin   = 9;
const int echoPin   = 10;
const int servoPin  = 6;
const int buzzerPin = 7;
const int greenLED  = 5;
const int redLED    = 4;

// -------- Objects --------
Servo lid;

// -------- Variables --------
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  lid.attach(servoPin);
  lid.write(0);                 // Lid closed

  digitalWrite(redLED, HIGH);   // Red ON initially
  digitalWrite(greenLED, LOW);
}

void loop() {
  // ----- Ultrasonic Trigger -----
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // ----- Measure Echo -----
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // ----- Smart Dustbin Logic -----
  if (distance > 0 && distance < 15) {   // Hand detected
    lid.write(90);                       // Open lid

    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);

    tone(buzzerPin, 1000);               // Beep
    delay(300);
    noTone(buzzerPin);

    delay(2000);                         // Lid open time
  } 
  else {
    lid.write(0);                        // Close lid
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
  }

  delay(200);
}
