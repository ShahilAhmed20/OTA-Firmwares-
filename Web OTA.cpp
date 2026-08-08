#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

// ====== CHANGE THESE ======
const char* ssid     = "Shahil";
const char* password = "connect2me";

IPAddress local_IP(10, 231, 18, 222);
IPAddress gateway(10, 231, 18, 1);
IPAddress subnet(255, 255, 255, 0);
// ==========================

const int LED_PIN = 2;
WebServer server(80);

// Simple HTML page for uploading
const char* uploadPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 WebOTA</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; background: #111; color: #eee; }
    .btn { background: #007bff; color: white; padding: 12px 25px; border: none; border-radius: 6px; font-size: 16px; cursor: pointer; }
    input[type=file] { margin: 20px; }
  </style>
</head>
<body>
  <h2>ESP32 Firmware Update</h2>
  <form method="POST" action="/update" enctype="multipart/form-data">
    <input type="file" name="update" accept=".bin">
    <br><br>
    <input type="submit" value="Upload Firmware" class="btn">
  </form>
  <p id="status"></p>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);          // LED always ON

  // Static IP
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Failed to configure static IP");
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // ========== Web Server Routes ==========
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", uploadPage);
  });

  server.on("/update", HTTP_POST, []() {
  server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
  delay(500);
  ESP.restart();
}, []() {
  HTTPUpload& upload = server.upload();

  if (upload.status == UPLOAD_FILE_START) {
    Serial.printf("Update: %s\n", upload.filename.c_str());
    if (!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)) {
      Update.printError(Serial);
    }
  } 
  else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } 
  else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) {
      Serial.printf("Update Success: %u bytes\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
  }
});
  server.begin();
  Serial.println("WebOTA Ready!");
  Serial.println("Open http://" + WiFi.localIP().toString() + " in your browser");
}

void loop() {
  server.handleClient();
}

