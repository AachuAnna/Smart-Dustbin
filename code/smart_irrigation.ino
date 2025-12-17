#include <LiquidCrystal.h>

/*
  Smart Irrigation System
  - Soil moisture based irrigation
  - Rain mode (manual override)
  - Predictive drying detection
  - LED represents pump (simulation-safe)
*/

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Pin definitions
const int soilPin   = A0;
const int pumpLED   = 8;   // LED represents pump
const int rainButton = 9;  // Rain mode button

// Variables
int soilValue = 0;
int prevSoilValue = 0;

// Thresholds (adjust if needed)
const int DRY_THRESHOLD = 450;
const int DRYING_RATE   = 20;

void setup() {
  pinMode(pumpLED, OUTPUT);
  pinMode(rainButton, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();

  // Initial soil reading
  prevSoilValue = analogRead(soilPin);
}

void loop() {
  soilValue = analogRead(soilPin);
  bool rainMode = (digitalRead(rainButton) == LOW);

  // Predictive logic: detect fast drying
  bool dryingFast = (prevSoilValue - soilValue) > DRYING_RATE;

  // Display soil value
  lcd.setCursor(0, 0);
  lcd.print("Soil:");
  lcd.print(soilValue);
  lcd.print("   ");

  if (rainMode) {
    // Rain mode forces pump OFF
    digitalWrite(pumpLED, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Rain Mode ON   ");
  }
  else if (soilValue > DRY_THRESHOLD || dryingFast) {
    // Soil dry or drying fast
    digitalWrite(pumpLED, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Pump ON        ");
  }
  else {
    // Soil sufficiently wet
    digitalWrite(pumpLED, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Pump OFF       ");
  }

  prevSoilValue = soilValue;
  delay(1000);
}
