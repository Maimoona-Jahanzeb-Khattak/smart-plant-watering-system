/*
  Smart Plant Watering System
  ----------------------------
  Reads soil moisture and automatically waters the plant
  using a water pump when the soil gets too dry.

  Components:
    - ESP32 (or Arduino Uno)
    - Capacitive soil moisture sensor
    - 5V relay module
    - Small submersible water pump
    - LED (optional, watering indicator)

  Author: Maimoona Jahanzeb Khattak
*/

// ---------- Pin setup ----------
const int MOISTURE_PIN = 34;   // Analog pin (ESP32 ADC pin). Use A0 on Arduino Uno.
const int RELAY_PIN     = 26;  // Digital pin controlling the relay (pump)
const int LED_PIN       = 2;   // Built-in LED on most ESP32 boards

// ---------- Settings ----------
const int DRY_THRESHOLD   = 2800;   // Raw sensor value below which soil counts as "dry"
                                     // Lower raw value = wetter soil (for most capacitive sensors)
const unsigned long PUMP_ON_TIME   = 5000;   // How long to run the pump per watering (ms)
const unsigned long CHECK_INTERVAL = 3600000; // How often to check soil moisture (ms) - default: 1 hour

unsigned long lastCheckTime = 0;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);  // Make sure pump starts OFF
  digitalWrite(LED_PIN, LOW);

  Serial.println("Smart Plant Watering System starting...");
}

void loop() {
  unsigned long currentTime = millis();

  // Only check moisture every CHECK_INTERVAL, instead of constantly
  if (currentTime - lastCheckTime >= CHECK_INTERVAL || lastCheckTime == 0) {
    lastCheckTime = currentTime;
    checkSoilAndWater();
  }
}

void checkSoilAndWater() {
  int moistureValue = analogRead(MOISTURE_PIN);
  int moisturePercent = map(moistureValue, 4095, 0, 0, 100); // Adjust 4095 if using Arduino Uno (use 1023 instead)

  Serial.print("Raw sensor value: ");
  Serial.print(moistureValue);
  Serial.print("  |  Estimated moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  if (moistureValue > DRY_THRESHOLD) {
    Serial.println("Soil is dry -> Watering plant...");
    waterPlant();
  } else {
    Serial.println("Soil moisture is fine. No watering needed.");
  }
}

void waterPlant() {
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(RELAY_PIN, HIGH);  // Turn pump ON
  delay(PUMP_ON_TIME);
  digitalWrite(RELAY_PIN, LOW);   // Turn pump OFF
  digitalWrite(LED_PIN, LOW);
  Serial.println("Watering complete.");
}
