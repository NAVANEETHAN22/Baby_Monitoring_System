#include <SoftwareSerial.h>

#define TEMP_PIN A0 // Analog pin for temperature sensor (LM35)
#define POT_PIN A1  // Analog pin for potentiometer
#define BUZZER_PIN 7
#define PIR_PIN 3
int potValue = 0;
float temperature = 0;

SoftwareSerial espSerial(5,6); // RX, TX pins for ESP8266 communication

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600); // Initialize ESP8266 communication
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(TEMP_PIN);
  temperature = (sensorValue / 1023.0) * 500; // Convert sensor value to temperature in Celsius
  Serial.println("temp");
  Serial.println(temperature);

  int pirState = digitalRead(PIR_PIN);
  if (pirState == HIGH) {
    Serial.print("Motion Detected!");

    delay(1000); // Buzzer on for 1 second
    // digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
    tone(BUZZER_PIN, 10);
    delay(500); // Wait for a short period to avoid multiple detections

    // Read potentiometer value
    potValue = analogRead(POT_PIN);
    Serial.println("Potentiometer Value: ");
    Serial.print(potValue);

    // Send data to ESP8266
    espSerial.print("Motion Detected! Temperature: ");
    espSerial.print(temperature);
    espSerial.print(" Potentiometer Value: ");
    espSerial.println(potValue);

  } else {
    tone(BUZZER_PIN, 10000000000000); //lcd.clear();
    //lcd.setCursor(0, 0);
    Serial.println("No Motion");
  }
  delay(2000);
}
