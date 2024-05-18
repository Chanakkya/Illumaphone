#include <SoftwareSerial.h>
#define RX_PIN 2
#define TX_PIN 3

SoftwareSerial espSerial(RX_PIN, TX_PIN);
void setup() {
  Serial.begin(9600); // Initialize hardware serial communication for debugging
  espSerial.begin(9600); // Initialize SoftwareSerial communication for ESP8266
}

void loop() {
  for (int i = 0; i < 6; i++) {
    int val = analogRead(i);
    espSerial.print(val); // Send analog reading to ESP8266
    Serial.print(val);
    if (i < 5) {
      espSerial.print(","); // Send comma-separated values
      Serial.print(",");
    }
  }
  espSerial.println(); // Send newline to separate each set of readings
  Serial.println();
  delay(5000); // Send data every 5 seconds
}