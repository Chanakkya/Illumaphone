#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "realme 1";       // Your WiFi SSID
const char* password = "a6051006e7bb";   // Your WiFi password

const char* server = "api.thingspeak.com"; // ThingSpeak server
const char* apiKey = "5E584IXQD8EA22F8";         // Your ThingSpeak API Key

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to WiFi
  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  String data = "api_key=";
  data += apiKey;
  if (Serial.available() > 0) 
  {
    String receivedData = Serial.readStringUntil('\n');
    int values[6]; // Array to store individual values
    int startIndex = 0;
    int endIndex = 0;
    for (int i = 0; i < 6; i++) {
      endIndex = receivedData.indexOf(',', startIndex); // Find index of next comma
      if (endIndex == -1) { // If no comma found, consider the rest of the string
        endIndex = receivedData.length();
      }
      values[i] = receivedData.substring(startIndex, endIndex).toInt(); // Extract and convert substring to integer
      startIndex = endIndex + 1; // Move startIndex to the next character after comma
    }
    for (int i = 0; i < 6; i++) {
    int val = values[i];
    data += "&field";
    data += String(i+1);
    data += "=";
    data += String(val);
  }
    
    if (sendToThingSpeak(data)) {
      Serial.print(data);
      Serial.println("Data sent to ThingSpeak successfully");
    } else {
      Serial.println("Failed to send data to ThingSpeak");
    }
  }
  
  delay(15000); // Update ThingSpeak every 15 seconds
}

bool sendToThingSpeak(String data) {
  WiFiClient client;
  if (!client.connect(server, 80)) {
    return false;
  }

  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(data.length());
  client.print("\n\n");
  client.print(data);

  

  delay(500);

  client.stop();

  return true;
}
