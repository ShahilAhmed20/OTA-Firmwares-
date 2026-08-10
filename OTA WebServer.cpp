#include <WiFi.h>
#include <HTTPUpdate.h>
#include <WiFiClient.h>

// ====== CHANGE THESE ======
const char* ssid     = "Shahil";
const char* password = "connect2me";

// Your computer's IP (the one running Python server)
// Example: if your laptop IP is 10.231.18.45
const char* firmwareURL = "10.231.18.45";
// ==========================

const int LED_PIN = 2;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(500);  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  delay(500); // LED Blinking 

  Serial.println("Connecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Start OTA update
  Serial.println("Checking for update...");
  WiFiClient client;
  
  t_httpUpdate_return ret = httpUpdate.update(client, firmwareURL);

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("Update failed! Error (%d): %s\n", 
                    httpUpdate.getLastError(), 
                    httpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No update available.");
      break;

    case HTTP_UPDATE_OK:
      Serial.println("Update successful! Restarting...");
      break;
  }
}

void loop() {
  // Nothing needed here
}