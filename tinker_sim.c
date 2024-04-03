#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TEMP_PIN A0 // Analog pin for temperature sensor (LM35)
#define POT_PIN A1  // Analog pin for potentiometer
#define BUZZER_PIN 4
#define PIR_PIN 3

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust I2C address and LCD size if necessary

int potValue = 0;
float temperature = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init(); // Initialize the LCD
  lcd.backlight();
}

void loop() {
  int pirState = digitalRead(PIR_PIN);
  if (pirState == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motion Detected!");

    digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
    delay(1000); // Buzzer on for 1 second
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer

    delay(500); // Wait for a short period to avoid multiple detections

    // Read temperature from LM35
    int sensorValue = analogRead(TEMP_PIN);
    temperature = (sensorValue / 1023.0) * 500; // Convert sensor value to temperature in Celsius

    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    // Read potentiometer value
    potValue = analogRead(POT_PIN);
    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);

    delay(2000); // Delay between readings
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Motion");

    delay(2000);
  }
}