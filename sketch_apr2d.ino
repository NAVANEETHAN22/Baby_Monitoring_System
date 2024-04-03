// Define pin numbers
const int pumpPin = 9;          // Pin connected to the MOSFET gate
const int moisturePin = A0;     // Analog pin connected to the soil moisture sensor
const int buzzerPin = 10;       // Pin connected to the buzzer
const int tempPin = A1;         // Analog pin connected to the LM35 temperature sensor

void setup() {
  // Initialize pump pin, buzzer pin, and temperature pin as outputs
  pinMode(pumpPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Start serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Read soil moisture sensor value
  int moistureValue = analogRead(moisturePin);
  
  // Read temperature sensor value
  int tempValue = analogRead(tempPin);
  float temperature = (tempValue * 5.0) / 1023.0 * 100.0;  // Convert to Celsius
  
  // Print the moisture and temperature values to serial monitor (optional)
  Serial.print("Moisture Value: ");
  Serial.println(moistureValue);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  // Check moisture level and control the pump and buzzer accordingly
  if (moistureValue > 500 && temperature < 30.0) {
    // Turn on the pump
    digitalWrite(pumpPin, HIGH);
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
    Serial.println("Pump ON");
  } else {
    // Turn off the pump and buzzer
    digitalWrite(pumpPin, LOW);
    digitalWrite(buzzerPin, LOW);   // Turn off the buzzer
    Serial.println("Pump OFF");
  }
  
  // Delay before next iteration
  delay(1000); // Adjust as needed
}
